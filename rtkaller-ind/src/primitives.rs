// Copyright 2021, Developed by Tsinghua Wingtecher Lab and Shumuyulin Ltd, All rights reserved.
use crate::model::{APPConfig, HookType, InstType, Task};
use crate::prog::Call;
use bitflags::_core::cell::Cell;
use rand::prelude::{IteratorRandom, SliceRandom};
use rand::{random, thread_rng, Rng};

pub static POSSIBLE_SIZE: [u8; 4] = [8, 16, 32, 64];

thread_local! {
    pub static REG_SIZE: Cell<u8> = Cell::new(32);
}

pub fn rand_call(app: &APPConfig, tp: &InstType) -> Call {
    const PRIMITIVES: [fn(&APPConfig, &InstType) -> Call; 6] = [
        rand_task_call,
        rand_int_call,
        rand_res_call,
        rand_event_call,
        rand_cnt_call,
        rand_other,
    ];
    let mut rng = thread_rng();
    PRIMITIVES.choose(&mut rng).unwrap()(app, tp)
}

pub fn rand_task_call(app: &APPConfig, tp: &InstType) -> Call {
    let mut rng = thread_rng();
    match tp {
        InstType::Task(_) => match rng.gen_range(0, 5) {
            0 => activate_task(app),
            1 => sched(),
            2 => f_sched(),
            3 => get_task_id(),
            4 => get_task_state(app),
            _ => unreachable!(),
        },
        InstType::Isr(isr) => {
            if isr.is_isr1 {
                rand_isr1()
            } else {
                match rng.gen_range(0, 3) {
                    0 => activate_task(app),
                    1 => get_task_id(),
                    2 => get_task_state(app),
                    _ => unreachable!(),
                }
            }
        }
        InstType::Hook(h) => match *h {
            HookType::STARTUP => rand_startup_hook(),
            HookType::SHUTDOWN => rand_shutdown_hook(),
            _ => match rng.gen_range(0, 2) {
                0 => get_task_id(),
                1 => get_task_state(app),
                _ => unreachable!(),
            },
        },
    }
}

pub fn rand_int_call(_app: &APPConfig, tp: &InstType) -> Call {
    let mut rng = thread_rng();
    if let InstType::Hook(h) = tp {
        match *h {
            HookType::STARTUP => rand_startup_hook(),
            HookType::SHUTDOWN => rand_shutdown_hook(),
            _ => match rng.gen_range(0, 2) {
                0 => suspend_int(),
                1 => resume_int(),
                _ => unreachable!(),
            },
        }
    } else {
        rand_isr1()
    }
}

pub fn rand_res_call(_app: &APPConfig, tp: &InstType) -> Call {
    match tp {
        InstType::Task(t) => {
            if random() {
                let (_, call) = get_res(t);
                call
            } else {
                release_res(None)
            }
        }
        InstType::Isr(_) => {
            // TODO Add resource to isr
            release_res(None)
        }
        InstType::Hook(_) => rand_shutdown_hook(),
    }
}

pub fn rand_event_call(app: &APPConfig, tp: &InstType) -> Call {
    let mut rng = thread_rng();
    match tp {
        InstType::Task(t) => match rng.gen_range(0, 4) {
            0 => set_event(app),
            1 => clear_event(t),
            2 => get_event(app),
            3 => {
                let (_, call) = wait_event(t);
                call
            }
            _ => unreachable!(),
        },
        InstType::Isr(isr) => {
            if isr.is_isr1 {
                rand_isr1()
            } else {
                match rng.gen_range(0, 1) {
                    0 => set_event(app),
                    1 => get_event(app),
                    _ => unreachable!(),
                }
            }
        }
        InstType::Hook(h) => match *h {
            HookType::STARTUP => rand_startup_hook(),
            HookType::SHUTDOWN => rand_shutdown_hook(),
            _ => get_event(app),
        },
    }
}

pub fn rand_cnt_call(app: &APPConfig, tp: &InstType) -> Call {
    match tp {
        InstType::Task(_t) => rand_cnt_all(app),
        InstType::Isr(isr) => {
            if isr.is_isr1 {
                rand_isr1()
            } else {
                rand_cnt_all(app)
            }
        }
        InstType::Hook(h) => {
            let mut rng = thread_rng();
            match *h {
                HookType::STARTUP => rand_startup_hook(),
                HookType::SHUTDOWN => rand_shutdown_hook(),
                _ => match rng.gen_range(0, 2) {
                    0 => get_alarm_base(app),
                    1 => get_alarm(app),
                    _ => unreachable!(),
                },
            }
        }
    }
}

pub fn rand_other(_app: &APPConfig, tp: &InstType) -> Call {
    let mut rng = thread_rng();
    match tp {
        InstType::Task(_) => match rng.gen_range(0, 3) {
            0 => get_app_mode(),
            1 => start_os(),
            2 => shutdown(),
            _ => unreachable!(),
        },
        InstType::Isr(isr) => {
            if isr.is_isr1 {
                rand_isr1()
            } else if random() {
                get_app_mode()
            } else {
                shutdown()
            }
        }
        InstType::Hook(h) => match *h {
            HookType::ERROR | HookType::STARTUP => rand_startup_hook(),
            _ => rand_shutdown_hook(),
        },
    }
}

fn rand_shutdown_hook() -> Call {
    get_app_mode()
}

fn rand_startup_hook() -> Call {
    if random() {
        get_app_mode()
    } else {
        shutdown()
    }
}

fn rand_isr1() -> Call {
    let mut rng = thread_rng();
    match rng.gen_range(0, 6) {
        0 => disable_int(),
        1 => enable_int(),
        2 => suspend_int(),
        3 => resume_int(),
        4 => suspend_os_int(),
        5 => resume_os_int(),
        _ => unreachable!(),
    }
}

fn rand_cnt_all(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    match rng.gen_range(0, 8) {
        0 => inc_counter(app),
        1 => get_alarm_base(app),
        2 => get_alarm(app),
        3 => set_rel_alarm(app),
        4 => set_abs_alarm(app),
        5 => cancel_alarm(app),
        6 => get_counter_value(app),
        7 => get_elapsed(app),
        _ => unreachable!(),
    }
}

fn rand_reg_num(signed: bool) -> i64 {
    let mut reg_size = 32;
    REG_SIZE.with(|f| reg_size = f.get());

    let mut rng = thread_rng();
    match (reg_size, signed) {
        (8, true) => rng.gen::<i8>() as i64,
        (8, false) => rng.gen::<u8>() as i64,
        (16, true) => rng.gen::<i16>() as i64,
        (16, false) => rng.gen::<u16>() as i64,
        (32, true) => rng.gen::<i32>() as i64,
        (32, false) | (64, false) => rng.gen::<u32>() as i64,
        (64, true) => rng.gen(),
        _ => unreachable!(),
    }
}

fn rand_reg_signed() -> i64 {
    rand_reg_num(true)
}

fn rand_reg_unsigned() -> i64 {
    rand_reg_num(false)
}

fn activate_task(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    if rng.gen::<f32>() < 0.1 {
        Call::activate_task_1(rand_reg_signed())
    } else {
        let t = app.tasks.choose(&mut rng).unwrap();
        Call::activate_task(&t.id)
    }
}

pub fn chain_task(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    if rng.gen::<f32>() < 0.1 {
        Call::chain_task_1(rand_reg_signed())
    } else {
        let t = app.tasks.choose(&mut rng).unwrap();
        Call::chain_task(&t.id)
    }
}

#[inline]
fn sched() -> Call {
    Call::sched()
}

#[inline]
fn f_sched() -> Call {
    Call::f_sched()
}

#[inline]
fn get_task_id() -> Call {
    Call::get_task_id()
}

fn get_task_state(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    if rng.gen::<f32>() < 0.1 {
        Call::get_task_state_1(rand_reg_signed())
    } else {
        let t = app.tasks.choose(&mut rng).unwrap();
        Call::get_task_state(&t.id)
    }
}

#[inline]
fn disable_int() -> Call {
    Call::disable_int()
}

#[inline]
fn enable_int() -> Call {
    Call::enable_int()
}

#[inline]
fn suspend_int() -> Call {
    Call::suspend_int()
}

#[inline]
fn resume_int() -> Call {
    Call::resume_int()
}

#[inline]
fn suspend_os_int() -> Call {
    Call::suspend_os_int()
}

#[inline]
fn resume_os_int() -> Call {
    Call::resume_os_int()
}

fn get_res(t: &Task) -> (Option<String>, Call) {
    let mut rng = thread_rng();
    if t.resources.is_empty() || rng.gen::<f32>() < 0.1 {
        (None, Call::get_res_1(rand_reg_unsigned()))
    } else {
        let r = t.resources.choose(&mut rng).unwrap();
        (Some(r.clone()), Call::get_res(&r))
    }
}

fn release_res(r: Option<&str>) -> Call {
    if let Some(r) = r {
        Call::release_res(r)
    } else {
        Call::release_res_1(rand_reg_unsigned())
    }
}

fn set_event(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let t = app
        .tasks
        .iter()
        .filter(|t| !t.events.is_empty())
        .choose(&mut rng);
    if let Some(t) = t {
        set_task_event(t)
    } else {
        Call::set_event_1(rand_reg_signed(), rand_reg_unsigned())
    }
}

fn set_task_event(t: &Task) -> Call {
    let mut rng = thread_rng();
    let e = t.events.choose(&mut rng);
    if let Some(e) = e {
        if rng.gen::<f32>() > 0.08 {
            Call::set_event(&t.id, &e)
        } else {
            Call::set_event_2(&t.id, rand_reg_unsigned())
        }
    } else {
        Call::set_event_2(&t.id, rand_reg_unsigned())
    }
}

fn clear_event(t: &Task) -> Call {
    let mut rng = thread_rng();
    let e = t.events.choose(&mut rng);
    if let Some(e) = e {
        if rng.gen::<f32>() > 0.09 {
            Call::clear_event(&e)
        } else {
            Call::clear_event_1(rand_reg_unsigned())
        }
    } else {
        Call::clear_event_1(rand_reg_unsigned())
    }
}

fn get_event(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let t = app
        .tasks
        .iter()
        .filter(|t| !t.events.is_empty())
        .choose(&mut rng);
    if let Some(t) = t {
        if rng.gen::<f32>() > 0.09 {
            Call::get_event(&t.id)
        } else {
            Call::get_event_1(rand_reg_unsigned())
        }
    } else {
        Call::get_event_1(rand_reg_unsigned())
    }
}

fn wait_event(t: &Task) -> (Option<String>, Call) {
    let mut rng = thread_rng();
    if t.events.is_empty() {
        (None, Call::wait_event_1(rand_reg_unsigned()))
    } else {
        let e = t.events.choose(&mut rng).unwrap();
        if rng.gen::<f32>() > 0.09 {
            (Some(e.clone()), Call::wait_event(&e))
        } else {
            (None, Call::wait_event_1(rand_reg_unsigned()))
        }
    }
}

fn inc_counter(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let c = app.counters.choose(&mut rng);
    if let Some(c) = c {
        if rng.gen::<f32>() > 0.09 {
            Call::inc_counter(&c)
        } else {
            Call::inc_counter_1(rand_reg_signed())
        }
    } else {
        Call::inc_counter_1(rand_reg_unsigned())
    }
}

fn get_counter_value(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let c = app.counters.choose(&mut rng);
    if let Some(c) = c {
        if rng.gen::<f32>() > 0.09 {
            Call::get_counter_value(&c)
        } else {
            Call::get_counter_value_1(rand_reg_signed())
        }
    } else {
        Call::get_counter_value_1(rand_reg_unsigned())
    }
}

fn get_elapsed(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let c = app.counters.choose(&mut rng);
    if let Some(c) = c {
        if rng.gen::<f32>() > 0.09 {
            Call::get_elapsed(&c)
        } else {
            Call::get_elapsed_1(rand_reg_signed())
        }
    } else {
        Call::get_elapsed_1(rand_reg_unsigned())
    }
}

fn get_alarm_base(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let a = app.alarms.choose(&mut rng);
    if let Some(a) = a {
        if rng.gen::<f32>() > 0.09 {
            Call::get_alarm_base(&a)
        } else {
            Call::get_alarm_base_1(rand_reg_signed())
        }
    } else {
        Call::get_alarm_base_1(rand_reg_unsigned())
    }
}

pub fn get_alarm(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let a = app.alarms.choose(&mut rng);
    if let Some(a) = a {
        if rng.gen::<f32>() > 0.09 {
            Call::get_alarm(&a)
        } else {
            Call::get_alarm_1(rand_reg_signed())
        }
    } else {
        Call::get_alarm_1(rand_reg_unsigned())
    }
}

fn set_rel_alarm(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let a = app.alarms.choose(&mut rng);
    if let Some(a) = a {
        if rng.gen::<f32>() > 0.09 {
            Call::set_rel_alarm(&a, rand_reg_unsigned(), rand_reg_unsigned())
        } else {
            Call::set_rel_alarm_1(rand_reg_signed(), rand_reg_unsigned(), rand_reg_unsigned())
        }
    } else {
        Call::set_rel_alarm_1(rand_reg_signed(), rand_reg_unsigned(), rand_reg_unsigned())
    }
}

fn set_abs_alarm(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let a = app.alarms.choose(&mut rng);
    if let Some(a) = a {
        if rng.gen::<f32>() > 0.09 {
            Call::set_abs_alarm(&a, rand_reg_unsigned(), rand_reg_unsigned())
        } else {
            Call::set_abs_alarm_1(rand_reg_signed(), rand_reg_unsigned(), rand_reg_unsigned())
        }
    } else {
        Call::set_abs_alarm_1(rand_reg_signed(), rand_reg_unsigned(), rand_reg_unsigned())
    }
}

pub fn cancel_alarm(app: &APPConfig) -> Call {
    let mut rng = thread_rng();
    let a = app.alarms.choose(&mut rng);
    if let Some(a) = a {
        if rng.gen::<f32>() > 0.09 {
            Call::cancel_alarm(&a)
        } else {
            Call::cancel_alarm_1(rand_reg_signed())
        }
    } else {
        Call::cancel_alarm_1(rand_reg_signed())
    }
}

#[inline]
fn get_app_mode() -> Call {
    Call::get_app_mode()
}

#[inline]
fn start_os() -> Call {
    Call::start_os()
}

fn shutdown() -> Call {
    Call::shutdown(random::<u8>() as i64)
}
