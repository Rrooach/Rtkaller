// Copyright 2021, Developed by Tsinghua Wingtecher Lab and Shumuyulin Ltd, All rights reserved.
use crate::model::{APPConfig, HookType, Id, ISR};
use std::fmt;
use std::fmt::Display;

#[derive(Debug, Clone)]
pub struct Inst {
    pub tasks: Vec<TaskInst>,
    pub hooks: HookInst,
    pub isr: Vec<ISRInst>,
    // pub global_decls: Vec<Decl>,
}

impl Inst {
    pub fn new(app: &APPConfig) -> Self {
        let isr = app.isr.iter().map(|isr| ISRInst::with_meta(isr)).collect();
        let tasks = app
            .tasks
            .iter()
            .map(|t| TaskInst::new(t.id.clone()))
            .collect();
        let hooks = HookInst::new(app.enabled_hook);
        Self { tasks, hooks, isr }
    }
    pub fn to_cprog(&self) -> String {
        todo!()
    }
}

#[derive(Debug, Clone)]
pub struct TaskInst {
    pub id: Id,
    pub seq: Vec<Call>,
}

impl TaskInst {
    pub fn new(id: Id) -> Self {
        Self {
            id,
            seq: Default::default(),
        }
    }

    pub fn to_cprog(&self) -> String {
        todo!()
    }
}

#[derive(Debug, Clone)]
pub struct HookInst {
    pub enabled: HookType,
    pub error: Option<Vec<Call>>,
    pub startup: Option<Vec<Call>>,
    pub shutdown: Option<Vec<Call>>,
    pub pre_task: Option<Vec<Call>>,
    pub post_task: Option<Vec<Call>>,
}

pub struct IterHook<'a> {
    i: usize,
    hook: &'a HookInst,
}

impl<'a> Iterator for IterHook<'a> {
    type Item = (HookType, &'a [Call]);

    fn next(&mut self) -> Option<Self::Item> {
        if self.i == 5 {
            return None;
        }

        loop {
            match self.i {
                0 => {
                    self.i += 1;
                    if let Some(err_hook) = &self.hook.error {
                        return Some((HookType::ERROR, err_hook));
                    }
                }
                1 => {
                    self.i += 1;
                    if let Some(pre_hook) = &self.hook.pre_task {
                        return Some((HookType::PRE_TASK, pre_hook));
                    }
                }
                2 => {
                    self.i += 1;
                    if let Some(post_hook) = &self.hook.post_task {
                        return Some((HookType::POST_TASK, post_hook));
                    }
                }
                3 => {
                    self.i += 1;
                    if let Some(startup_hook) = &self.hook.startup {
                        return Some((HookType::STARTUP, startup_hook));
                    }
                }
                4 => {
                    self.i += 1;
                    if let Some(shutdown_hook) = &self.hook.shutdown {
                        return Some((HookType::SHUTDOWN, shutdown_hook));
                    }
                }
                _ => return None,
            }
        }
    }
}

// pub struct IterHookMut<'a> {
//     i: usize,
//     hook: &'a mut HookInst,
// }
//
// impl<'a> Iterator for IterHookMut<'a> {
//     type Item = (HookType, &'a mut Vec<Call>);
//
//     fn next(&mut self) -> Option<Self::Item > {
//         if self.i == 5 {
//             return None;
//         }
//
//         loop {
//             match self.i {
//                 0 => {
//                     self.i += 1;
//                     if let Some(err_hook) =  (*self).hook.error.as_mut() {
//                         return Some((HookType::ERROR, err_hook));
//                     }
//                 }
//                 1 => {
//                     self.i += 1;
//                     if let Some(pre_hook) = &mut self.hook.pre_task.as_mut() {
//                         return Some((HookType::PRE_TASK, pre_hook));
//                     }
//                 }
//                 2 => {
//                     self.i += 1;
//                     if let Some(post_hook) = &mut self.hook.post_task.as_mut() {
//                         return Some((HookType::POST_TASK, post_hook));
//                     }
//                 }
//                 3 => {
//                     self.i += 1;
//                     if let Some(startup_hook) = &mut self.hook.startup.as_mut() {
//                         return Some((HookType::STARTUP, startup_hook));
//                     }
//                 }
//                 4 => {
//                     self.i += 1;
//                     if let Some(shutdown_hook) = &mut self.hook.shutdown.as_mut() {
//                         return Some((HookType::SHUTDOWN, shutdown_hook));
//                     }
//                 }
//                 _ => return None
//             }
//         }
//     }
// }

impl HookInst {
    pub fn new(enabled: HookType) -> Self {
        let mut ret = Self {
            enabled,
            error: None,
            startup: None,
            shutdown: None,
            pre_task: None,
            post_task: None,
        };
        if enabled.contains(HookType::ERROR) {
            ret.error = Some(Vec::default())
        }
        if enabled.contains(HookType::STARTUP) {
            ret.startup = Some(Vec::default())
        }
        if enabled.contains(HookType::SHUTDOWN) {
            ret.shutdown = Some(Vec::default())
        }
        if enabled.contains(HookType::PRE_TASK) {
            ret.pre_task = Some(Vec::default())
        }
        if enabled.contains(HookType::POST_TASK) {
            ret.post_task = Some(Vec::default())
        }
        ret
    }

    pub fn iter_hook(&self) -> IterHook {
        IterHook { i: 0, hook: self }
    }

    // pub fn iter_hook_mut(&mut self) -> impl Iterator<Item=(HookType, &mut Vec<Call>)> + '_ {
    //     IterHookMut {
    //         i: 0,
    //         hook: self,
    //     }
    // }
}

#[derive(Debug, Clone)]
pub struct ISRInst {
    pub meta: ISR,
    pub seq: Vec<Call>,
}

impl ISRInst {
    pub fn with_meta(meta: &ISR) -> Self {
        Self {
            meta: meta.clone(),
            seq: Default::default(),
        }
    }

    pub fn to_cprog(&self) -> String {
        todo!()
    }
}

// #[derive(Debug, Clone)]
// pub struct Val<Call>(pub Vec<Call>);
//
// impl Default for Val<Call> {
//     fn default() -> Self {
//         Self(Vec::new())
//     }
// }

#[derive(Debug, Clone)]
pub struct Call {
    pub name: &'static str,
    pub args: Vec<Value>,
}

impl Call {
    pub fn activate_task(id: &str) -> Self {
        Self {
            name: "ActivateTask",
            args: vec![Value::Symbol(id.to_string())],
        }
    }
    pub fn activate_task_1(id: i64) -> Self {
        Self {
            name: "ActivateTask",
            args: vec![Value::Num(id)],
        }
    }

    pub fn term_task() -> Self {
        Self {
            name: "TerminateTask",
            args: vec![],
        }
    }

    pub fn chain_task(id: &str) -> Self {
        Self {
            name: "ChainTask",
            args: vec![Value::Symbol(id.to_string())],
        }
    }

    pub fn chain_task_1(id: i64) -> Self {
        Self {
            name: "ChainTask",
            args: vec![Value::Num(id)],
        }
    }

    pub fn sched() -> Self {
        Self {
            name: "Schedule",
            args: vec![],
        }
    }

    pub fn f_sched() -> Self {
        Self {
            name: "ForceSchedule",
            args: vec![],
        }
    }

    pub fn get_task_id() -> Self {
        Self {
            name: "GetTaskID",
            args: vec![Value::Ptr(PtrValue::Out("TaskType".to_string()))],
        }
    }

    pub fn get_task_state(id: &str) -> Self {
        Self {
            name: "GetTaskState",
            args: vec![
                Value::Symbol(id.to_string()),
                Value::Ptr(PtrValue::Out("TaskStateType".to_string())),
            ],
        }
    }

    pub fn get_task_state_1(id: i64) -> Self {
        Self {
            name: "GetTaskState",
            args: vec![
                Value::Num(id),
                Value::Ptr(PtrValue::Out("TaskStateType".to_string())),
            ],
        }
    }

    pub fn disable_int() -> Self {
        Self {
            name: "DisableAllInterrupts",
            args: vec![],
        }
    }

    pub fn enable_int() -> Self {
        Self {
            name: "EnableAllInterrupts",
            args: vec![],
        }
    }

    pub fn suspend_int() -> Self {
        Self {
            name: "SuspendAllInterrupts",
            args: vec![],
        }
    }

    pub fn resume_int() -> Self {
        Self {
            name: "ResumeAllInterrupts",
            args: vec![],
        }
    }

    pub fn suspend_os_int() -> Self {
        Self {
            name: "SuspendOSInterrupts",
            args: vec![],
        }
    }

    pub fn resume_os_int() -> Self {
        Self {
            name: "ResumeOSInterrupts",
            args: vec![],
        }
    }

    pub fn get_res(res_id: &str) -> Self {
        Self {
            name: "GetResource",
            args: vec![Value::Symbol(res_id.to_string())],
        }
    }

    pub fn get_res_1(res_id: i64) -> Self {
        Self {
            name: "GetResource",
            args: vec![Value::Num(res_id)],
        }
    }

    pub fn release_res(res_id: &str) -> Self {
        Self {
            name: "ReleaseResource",
            args: vec![Value::Symbol(res_id.to_string())],
        }
    }

    pub fn release_res_1(res_id: i64) -> Self {
        Self {
            name: "ReleaseResource",
            args: vec![Value::Num(res_id)],
        }
    }

    pub fn set_event(tid: &str, mask: &str) -> Self {
        Self {
            name: "SetEvent",
            args: vec![
                Value::Symbol(tid.to_string()),
                Value::Symbol(mask.to_string()),
            ],
        }
    }

    pub fn set_event_1(tid: i64, mask: i64) -> Self {
        Self {
            name: "SetEvent",
            args: vec![Value::Num(tid), Value::Num(mask)],
        }
    }

    pub fn set_event_2(tid: &str, mask: i64) -> Self {
        Self {
            name: "SetEvent",
            args: vec![Value::Symbol(tid.to_string()), Value::Num(mask)],
        }
    }

    pub fn set_event_3(tid: i64, mask: &str) -> Self {
        Self {
            name: "SetEvent",
            args: vec![Value::Num(tid), Value::Symbol(mask.to_string())],
        }
    }

    pub fn clear_event(mask: &str) -> Self {
        Self {
            name: "ClearEvent",
            args: vec![Value::Symbol(mask.to_string())],
        }
    }

    pub fn clear_event_1(mask: i64) -> Self {
        Self {
            name: "ClearEvent",
            args: vec![Value::Num(mask)],
        }
    }

    pub fn get_event(tid: &str) -> Self {
        Self {
            name: "GetEvent",
            args: vec![
                Value::Symbol(tid.to_string()),
                Value::Ptr(PtrValue::Out("EventMaskType".to_string())),
            ],
        }
    }

    pub fn get_event_1(tid: i64) -> Self {
        Self {
            name: "GetEvent",
            args: vec![
                Value::Num(tid),
                Value::Ptr(PtrValue::Out("EventMaskType".to_string())),
            ],
        }
    }

    pub fn wait_event(mask: &str) -> Self {
        Self {
            name: "WaitEvent",
            args: vec![Value::Symbol(mask.to_string())],
        }
    }

    pub fn wait_event_1(mask: i64) -> Self {
        Self {
            name: "WaitEvent",
            args: vec![Value::Num(mask)],
        }
    }

    pub fn inc_counter(counter: &str) -> Self {
        Self {
            name: "IncrementCounter",
            args: vec![Value::Symbol(counter.to_string())],
        }
    }

    pub fn inc_counter_1(counter: i64) -> Self {
        Self {
            name: "IncrementCounter",
            args: vec![Value::Num(counter)],
        }
    }

    pub fn get_counter_value(cid: &str) -> Self {
        Self {
            name: "GetCounterValue",
            args: vec![
                Value::Symbol(cid.to_string()),
                Value::Ptr(PtrValue::Out("TickType".to_string())),
            ],
        }
    }

    pub fn get_counter_value_1(cid: i64) -> Self {
        Self {
            name: "GetCounterValue",
            args: vec![
                Value::Num(cid),
                Value::Ptr(PtrValue::Out("TickType".to_string())),
            ],
        }
    }

    pub fn get_elapsed(cid: &str) -> Self {
        Self {
            name: "GetElapsedValue",
            args: vec![
                Value::Symbol(cid.to_string()),
                Value::Ptr(PtrValue::Out("TickType".to_string())),
                Value::Ptr(PtrValue::Out("TickType".to_string())),
            ],
        }
    }

    pub fn get_elapsed_1(cid: i64) -> Self {
        Self {
            name: "GetElapsedValue",
            args: vec![
                Value::Num(cid),
                Value::Ptr(PtrValue::Out("TickType".to_string())),
                Value::Ptr(PtrValue::Out("TickType".to_string())),
            ],
        }
    }

    pub fn get_alarm_base(aid: &str) -> Self {
        Self {
            name: "GetAlarmBase",
            args: vec![
                Value::Symbol(aid.to_string()),
                Value::Ptr(PtrValue::Out("AlarmBaseType".to_string())),
            ],
        }
    }

    pub fn get_alarm_base_1(aid: i64) -> Self {
        Self {
            name: "GetAlarmBase",
            args: vec![
                Value::Num(aid),
                Value::Ptr(PtrValue::Out("AlarmBaseType".to_string())),
            ],
        }
    }

    pub fn get_alarm(aid: &str) -> Self {
        Self {
            name: "GetAlarm",
            args: vec![
                Value::Symbol(aid.to_string()),
                Value::Ptr(PtrValue::Out("TickType".to_string())),
            ],
        }
    }

    pub fn get_alarm_1(aid: i64) -> Self {
        Self {
            name: "GetAlarm",
            args: vec![
                Value::Num(aid),
                Value::Ptr(PtrValue::Out("TickType".to_string())),
            ],
        }
    }

    pub fn set_rel_alarm(aid: &str, inc: i64, cycle: i64) -> Self {
        Self {
            name: "SetRelAlarm",
            args: vec![
                Value::Symbol(aid.to_string()),
                Value::Num(inc),
                Value::Num(cycle),
            ],
        }
    }

    pub fn set_rel_alarm_1(aid: i64, inc: i64, cycle: i64) -> Self {
        Self {
            name: "SetRelAlarm",
            args: vec![Value::Num(aid), Value::Num(inc), Value::Num(cycle)],
        }
    }

    pub fn set_abs_alarm(aid: &str, start: i64, cycle: i64) -> Self {
        Self {
            name: "SetAbsAlarm",
            args: vec![
                Value::Symbol(aid.to_string()),
                Value::Num(start),
                Value::Num(cycle),
            ],
        }
    }

    pub fn set_abs_alarm_1(aid: i64, start: i64, cycle: i64) -> Self {
        Self {
            name: "SetAbsAlarm",
            args: vec![Value::Num(aid), Value::Num(start), Value::Num(cycle)],
        }
    }

    pub fn cancel_alarm(aid: &str) -> Self {
        Self {
            name: "CancelAlarm",
            args: vec![Value::Symbol(aid.to_string())],
        }
    }

    pub fn cancel_alarm_1(aid: i64) -> Self {
        Self {
            name: "CancelAlarm",
            args: vec![Value::Num(aid)],
        }
    }

    pub fn get_app_mode() -> Self {
        Self {
            name: "GetActiveApplicationMode",
            args: vec![],
        }
    }

    pub fn start_os() -> Self {
        Self {
            name: "StartOS",
            args: vec![Value::Symbol("OSDEFAULTAPPMODE".to_string())],
        }
    }

    pub fn shutdown(err: i64) -> Self {
        Self {
            name: "ShutdownOS",
            args: vec![Value::Num(err)],
        }
    }
}

impl Display for Call {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}(", self.name)?;
        for i in 0..self.args.len() {
            write!(f, "{}", &self.args[i])?;
            if i != self.args.len() - 1 {
                write!(f, ",")?;
            }
        }
        write!(f, ")")
    }
}

#[derive(Debug, Clone)]
pub enum Value {
    Symbol(String),
    Num(i64),
    Ptr(PtrValue),
}

impl Value {
    pub fn symbol(&self) -> Option<String> {
        if let Value::Symbol(s) = self {
            Some(s.clone())
        } else {
            None
        }
    }
}

impl Display for Value {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Value::Symbol(s) => write!(f, "{}", s),
            Value::Num(n) => write!(f, "{}", n),
            Value::Ptr(val) => {
                // TODO opt
                write!(f, "{:?}", val)
            }
        }
    }
}

#[derive(Debug, Clone)]
pub enum PtrValue {
    Out(String),
    Ref(String),
    None,
}
