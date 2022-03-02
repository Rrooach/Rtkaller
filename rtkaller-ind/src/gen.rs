// Copyright 2021, Developed by Tsinghua Wingtecher Lab and Shumuyulin Ltd, All rights reserved.
use crate::gen::TaskState::WaitEvent;
use crate::model::{APPConfig, HookType, Id, InstType};
use crate::primitives::{chain_task, rand_call};
use crate::prog::{Call, HookInst, ISRInst, Inst, TaskInst, Value};
use rand::prelude::{IteratorRandom, SliceRandom};
use rand::{random, thread_rng, Rng};
use std::cmp::max;
use std::collections::HashMap;

#[derive(Debug, Hash, Eq, Ord, PartialOrd, PartialEq)]
enum TaskState {
    WaitEvent(Id),
    HoldRes(Id),
    Normal,
}

impl TaskState {
    pub fn waiting_event(&self) -> Option<Id> {
        if let WaitEvent(e) = self {
            Some(e.clone())
        } else {
            None
        }
    }
}

type Context = HashMap<Id, TaskState>;

pub fn gen(app: &APPConfig) -> Inst {
    let mut rng = thread_rng();
    let mut inst = Inst::new(app);
    let mut ctx = inst
        .tasks
        .iter()
        .map(|t| (t.id.clone(), TaskState::Normal))
        .collect();

    loop {
        match rng.gen_range(0, 9) {
            0..=5 => gen_task(&mut inst.tasks, &mut ctx, &app),
            6..=7 => {
                if rng.gen::<f32>() < 0.05 && app.isr.iter().any(|i| i.is_isr1) {
                    gen_isr1(&mut inst.isr, &mut ctx, app)
                } else {
                    gen_isr2(&mut inst.isr, &mut ctx, app)
                }
            }
            8 => gen_hook(&mut inst.hooks, &mut ctx, app),
            _ => unreachable!(),
        }
        if should_stop(&inst) {
            break;
        }
    }
    term_task(&mut inst.tasks, &app);

    inst
}

fn term_task(ts: &mut [TaskInst], app: &APPConfig) {
    for t in ts {
        if random() {
            t.seq.push(Call::term_task())
        } else {
            t.seq.push(chain_task(app))
        }
    }
}

fn should_stop(inst: &Inst) -> bool {
    let non_empty_all = inst.tasks.iter().all(|t| !t.seq.is_empty())
        && inst.isr.iter().all(|i| !i.seq.is_empty())
        && inst.hooks.iter_hook().all(|(_, s)| !s.is_empty());

    let task_max_length = inst
        .tasks
        .iter()
        .max_by_key(|t| t.seq.len())
        .unwrap()
        .seq
        .len();
    let isr_max_len = if let Some(i) = inst.isr.iter().max_by_key(|i| i.seq.len()) {
        i.seq.len()
    } else {
        0
    };
    let hook_max_len = if let Some((_, s)) = inst.hooks.iter_hook().max_by_key(|(_, s)| s.len()) {
        s.len()
    } else {
        0
    };

    let max_length = max(max(task_max_length, isr_max_len), hook_max_len);

    non_empty_all && max_length >= 4
}

fn gen_task(tasks: &mut [TaskInst], ctx: &mut Context, app: &APPConfig) {
    assert!(!tasks.is_empty());

    let mut rng = thread_rng();

    // prefer to choose a not-waiting task
    let t = if let Some(t) = tasks
        .iter_mut()
        .filter(|t| ctx[&t.id].waiting_event().is_none())
        .choose(&mut rng)
    {
        t
    } else {
        tasks.choose_mut(&mut rng).unwrap()
    };

    // try to wake up a waiting task first
    if let Some((task, event)) = waiting_task(ctx) {
        if ctx[&t.id].waiting_event().is_none() {
            t.seq.push(Call::set_event(&task, &event));
            ctx.insert(task, TaskState::Normal);
            return;
        }
    }

    // try to release resource
    if let TaskState::HoldRes(ref res) = &ctx[&t.id] {
        if rng.gen::<f32>() < 0.85 {
            t.seq.push(Call::release_res(res));
            ctx.insert(t.id.clone(), TaskState::Normal);
            return;
        }
    }

    // just add another call
    add_call(t, ctx, app)
}

fn add_call(t: &mut TaskInst, ctx: &mut Context, app: &APPConfig) {
    const HOLD_RES_BLACK_LIST: [&str; 3] = ["Schedule", "WaitEvent", "GetResource"];
    const WAITING_BLACK_LIST: [&str; 2] = ["WaitEvent", "GetResource"];

    let tp = InstType::Task(
        app.tasks
            .iter()
            .find(|task| task.id == t.id)
            .unwrap()
            .clone(),
    );

    loop {
        let c = rand_call(app, &tp);

        // forbid nest res occupy
        if let TaskState::HoldRes(_) = &ctx[&t.id] {
            if HOLD_RES_BLACK_LIST.contains(&c.name) {
                continue;
            }
        }

        if let TaskState::WaitEvent(_) = &ctx[&t.id] {
            if WAITING_BLACK_LIST.contains(&c.name) {
                continue;
            }
        }

        t.seq.push(c.clone());
        update_state(t, &c, ctx);
        break;
    }
}

fn update_state(t: &mut TaskInst, c: &Call, ctx: &mut Context) {
    let mut rng = thread_rng();

    match c.name {
        "DisableAllInterrupts" => {
            if rng.gen::<f32>() > 0.08 {
                t.seq.push(Call::enable_int());
                return;
            }
        }
        "SuspendAllInterrupts" => {
            if rng.gen::<f32>() > 0.08 {
                t.seq.push(Call::resume_int());
                return;
            }
        }
        "SuspendOSInterrupts" => {
            if rng.gen::<f32>() > 0.08 {
                t.seq.push(Call::resume_os_int());
                return;
            }
        }
        _ => (),
    }

    if let TaskState::HoldRes(res) = &ctx[&t.id] {
        if c.name == "ReleaseResource" && c.args[0].symbol().is_some() {
            let s = c.args[0].symbol().unwrap();
            if &s == res {
                ctx.insert(t.id.clone(), TaskState::Normal);
                return;
            }
        }
    }

    // Normal state
    if let TaskState::Normal = &ctx[&t.id] {
        match (c.name, c.args.get(0)) {
            ("GetResource", Some(Value::Symbol(res))) => {
                ctx.insert(t.id.clone(), TaskState::HoldRes(res.clone()));
            }
            ("WaitEvent", Some(Value::Symbol(event))) => {
                ctx.insert(t.id.clone(), TaskState::WaitEvent(event.clone()));
            }
            _ => (),
        }
    }
}

fn gen_isr1(isr: &mut [ISRInst], _ctx: &mut Context, app: &APPConfig) {
    let mut rng = thread_rng();
    if let Some(isr) = isr.iter_mut().choose(&mut rng) {
        let inst = InstType::Isr(isr.meta.clone());
        isr.seq.push(rand_call(app, &inst));
    }
}

fn gen_isr2(isr: &mut [ISRInst], ctx: &mut Context, app: &APPConfig) {
    let mut rng = thread_rng();
    let isr = isr.iter_mut().choose(&mut rng);
    if let Some(isr) = isr {
        if let Some((task, id)) = waiting_task(ctx) {
            isr.seq.push(Call::set_event(&task, &id));
            ctx.insert(task, TaskState::Normal);
        } else {
            let inst = InstType::Isr(isr.meta.clone());
            isr.seq.push(rand_call(app, &inst));
        }
    }
}

fn gen_hook(hook: &mut HookInst, _ctx: &mut Context, app: &APPConfig) {
    if hook.enabled.is_empty() {
        return;
    }

    // let mut rng = thread_rng();
    // if let Some((tp, seq)) =hook.iter_hook_mut().choose(&mut rng){
    //     let inst = InstType::Hook(tp);
    //     let c = rand_call(app, &inst);
    //     seq.push(c);
    // }

    let mut tp = vec![];
    let mut hooks = vec![];
    if let Some(s) = &mut hook.error {
        hooks.push(s);
        tp.push(HookType::ERROR);
    }
    if let Some(s) = &mut hook.pre_task {
        hooks.push(s);
        tp.push(HookType::PRE_TASK);
    }
    if let Some(s) = &mut hook.post_task {
        hooks.push(s);
        tp.push(HookType::POST_TASK);
    }
    if let Some(s) = &mut hook.startup {
        hooks.push(s);
        tp.push(HookType::STARTUP);
    }
    if let Some(s) = &mut hook.shutdown {
        hooks.push(s);
        tp.push(HookType::SHUTDOWN);
    }

    let i = thread_rng().gen_range(0, tp.len());
    let inst = InstType::Hook(tp[i]);
    let c = rand_call(app, &inst);
    hooks[i].push(c);
}

fn waiting_task(ctx: &Context) -> Option<(Id, Id)> {
    ctx.iter()
        .filter_map(|(id, state)| {
            let s = state.waiting_event();
            if let Some(s) = s {
                Some((id.clone(), s))
            } else {
                None
            }
        })
        .next()
}
