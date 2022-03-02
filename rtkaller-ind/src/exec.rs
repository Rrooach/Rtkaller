// Copyright 2021, Developed by Tsinghua Wingtecher Lab and Shumuyulin Ltd, All rights reserved.
//
use crate::prog::Inst;
use crate::translate::to_c;
use crate::Config;
use std::fs::write;
use std::io::Read;
use std::process::exit;
use std::time::Duration;
use subprocess::{Popen, PopenConfig, Redirection};

pub enum ExecResult {
    /// Test case executed successfully.
    /// Currently, feedback is just a stub for future extension.
    Success(Feedback),
    /// Test case executed failed.
    /// Currently, the only reason of failed test case is time out.
    Failed(String),
    /// Os crashed with related information.
    Crashed(String),
}

pub struct Feedback;

pub fn exec(p: &Inst, cfg: &Config) -> ExecResult {
    #[cfg(feature = "t32")]
    if !cfg.use_script {
        t32_exec(p, cfg)
    } else {
        script_exec(p, cfg)
    }

    #[cfg(not(feature = "t32"))]
    script_exec(p, cfg)
}

#[cfg(feature = "t32")]
fn t32_exec(p: &Inst, cfg: &Config) -> ExecResult {
    use t32_exec_impl::*;
    restart_os(cfg);
    serialize(p, cfg);
    if let Err(e) = wait_task_ready(p) {
        return ExecResult::Failed(e);
    }
    if let Err(e) = write_all(p) {
        return ExecResult::Failed(e);
    }
    monitor()
}

#[cfg(feature = "t32")]
mod t32_exec_impl {
    use super::*;
    use crate::model::HookType;
    use crate::prog::{Call, Inst, Value};
    use crate::t32;
    use crate::t32::read_u32;
    use crate::Config;
    use std::cell::Cell;
    use std::cell::RefCell;
    use std::collections::HashMap;
    use std::process::exit;
    use std::ptr::copy_nonoverlapping;
    use std::sync::Once;
    use std::thread::sleep;
    use std::time::Duration;

    pub fn restart_os(cfg: &Config) {
        use t32::PracticeState::*;

        if let Err(e) = t32::cmd(&cfg.restart_os_cmm_hook) {
            eprintln!(
                "Failed to execute restart os cmm hook: {:?}. cmm: {}",
                e, &cfg.restart_os_cmm_hook
            );
            exit(1)
        }
        if cfg.restart_os_cmm_hook.contains("DO") || cfg.restart_os_cmm_hook.contains("do") {
            while let Running = t32::get_practice_state().unwrap() {
                sleep(Duration::from_millis(5))
            }
        }
        t32::go();
        trace!("Os restarted");
    }

    const DEFAULT_LEN: usize = 1024;
    thread_local! {
        /* local storage for serialized result. Key is name of output variable.*/
        static SERIALIZED: RefCell<HashMap<String, [u8;DEFAULT_LEN]>> = RefCell::new(HashMap::new());
    }
    static INIT_SERIALIZED: Once = Once::new();

    // Init thread local *SERIALIZED* once.
    fn init_storage_once(inst: &Inst) {
        trace!("Serialized storage inited");
        INIT_SERIALIZED.call_once(|| {
            for (hp, _) in inst.hooks.iter_hook() {
                SERIALIZED.with(|s| {
                    s.borrow_mut()
                        .insert(hook_var_name(hp).to_string(), [0; DEFAULT_LEN]);
                })
            }

            for isr in &inst.isr {
                SERIALIZED.with(|s| {
                    s.borrow_mut()
                        .insert(isr_task_var_name(&isr.meta.id), [0; DEFAULT_LEN]);
                })
            }

            for task in &inst.tasks {
                SERIALIZED.with(|s| {
                    s.borrow_mut()
                        .insert(isr_task_var_name(&task.id), [0; DEFAULT_LEN]);
                })
            }

            SERIALIZED.with(|s| {
                s.borrow_mut().shrink_to_fit();
            })
        });
    }

    pub fn serialize(p: &Inst, cfg: &Config) {
        init_storage_once(p);
        serialize_hook(p, cfg);
        serialize_isr(p, cfg);
        serialize_tasks(p, cfg);
        trace!("Test case serialized");
    }

    fn serialize_hook(p: &Inst, cfg: &Config) {
        for (hp, calls) in p.hooks.iter_hook() {
            let var_name = hook_var_name(hp);
            serialize_item(&var_name, calls, cfg)
        }
    }

    fn hook_var_name(hp: HookType) -> &'static str {
        match hp {
            HookType::ERROR => "ERROR_HOOK_DATA",
            HookType::PRE_TASK => "PRE_TASK_DATA",
            HookType::POST_TASK => "POST_TASK_DATA",
            HookType::STARTUP => "STARTUP_DATA",
            HookType::SHUTDOWN => "SHUTDOWN_DATA",
            _ => unreachable!(),
        }
    }

    fn isr_task_var_name(id: &str) -> String {
        format!("{}_DATA", id)
    }

    fn serialize_tasks(p: &Inst, cfg: &Config) {
        for t in p.tasks.iter() {
            let var_name = isr_task_var_name(&t.id);
            serialize_item(&var_name, &t.seq, cfg)
        }
    }

    fn serialize_isr(p: &Inst, cfg: &Config) {
        for isr in p.isr.iter() {
            let var_name = isr_task_var_name(&isr.meta.id);
            serialize_item(&var_name, &isr.seq, cfg)
        }
    }

    fn serialize_item(name: &str, calls: &[Call], cfg: &Config) {
        SERIALIZED.with(|s| {
            let mut out = s.borrow_mut();
            let out = out.get_mut(name).unwrap();
            assert_eq!(out.len(), DEFAULT_LEN);

            serialize_calls(calls, cfg, out)
        });
    }

    fn serialize_calls(calls: &[Call], cfg: &Config, mut out: &mut [u8]) {
        const EOF: [u8; 4] = 0xFFFFu32.to_le_bytes();

        assert_eq!(out.len(), DEFAULT_LEN);
        let mut arg_left: usize;

        for c in calls {
            // make sure we have enough storage.
            assert!(out.len() >= 20);

            // write call id first.
            let id = id_of(c.name).to_le_bytes();
            unsafe {
                copy_nonoverlapping(id.as_ptr(), out[0..4].as_mut_ptr(), 4);
            }
            out = &mut out[4..];
            assert!(!out.is_empty());

            arg_left = 4;
            for arg in c.args.iter() {
                let val = serialize_value(arg, cfg).to_le_bytes();
                unsafe {
                    copy_nonoverlapping(val.as_ptr(), out[0..4].as_mut_ptr(), 4);
                }
                out = &mut out[4..];
                arg_left -= 1;
            }

            out = &mut out[4 * arg_left..];
        }
        unsafe {
            copy_nonoverlapping(EOF.as_ptr(), out[0..4].as_mut_ptr(), 4);
        }
    }

    fn serialize_value(v: &Value, cfg: &Config) -> u32 {
        match v {
            Value::Symbol(sym) => *cfg.app.sym_val.get(sym).unwrap_or_else(|| {
                eprintln!("Failed to resolve symbol value of \"{}\"", sym);
                exit(1)
            }),
            Value::Num(v) => *v as u32,
            Value::Ptr(_) => 0,
        }
    }

    fn id_of(call_name: &str) -> u32 {
        lazy_static! {
            static ref CID: HashMap<&'static str, u32> = {
                hashmap! {
                "ActivateTask" => 0,
                "TerminateTask" => 1,
                "ChainTask"  => 2,
                "Schedule" => 3,
                "ForceSchedule" => 4,
                "GetTaskID"                => 5,
                "GetTaskState"             => 6,
                "DisableAllInterrupts"     => 7,
                "EnableAllInterrupts"      => 8,
                "SuspendAllInterrupts"     => 9,
                "ResumeAllInterrupts"      => 10,
                "SuspendOSInterrupts"      => 11,
                "ResumeOSInterrupts"       => 12,
                "GetResource"              => 13,
                "ReleaseResource"          => 14,
                "SetEvent"                 => 15,
                "ClearEvent"               => 16,
                "GetEvent"                 => 17,
                "WaitEvent"                => 18,
                "IncrementCounter"         => 19,
                "GetAlarmBase"             => 20,
                "GetAlarm"                 => 21,
                "SetRelAlarm"              => 22,
                "SetAbsAlarm"              => 23,
                "CancelAlarm"              => 24,
                "GetActiveApplicationMode" => 25,
                "StartOS"                  => 26,
                "ShutdownOS"               => 27,
                "GetCounterValue"          => 28,
                "GetElapsedValue"          => 29,
                }
            };
        }
        *CID.get(call_name).unwrap_or_else(|| {
            eprintln!("Failed to map system call \"{}\" to id", call_name);
            exit(1)
        })
    }

    thread_local! {
        static TASKS_STATE_ADDR: RefCell<HashMap<String, u32>> = RefCell::new(HashMap::new());
    }
    static INIT_TASK_STATE_ADDR: Once = Once::new();

    const STATE_TASK_READY: u32 = 0x0001;
    const STATE_DATA_READY: u32 = 0x0010;
    const STATE_EXEC_FINISH: u32 = 0x1000;

    fn exec_finished() -> bool {
        t32::t32_break();
        let mut finished = false;
        TASKS_STATE_ADDR.with(|s| {
            for (var, addr) in s.borrow().iter() {
                if let Some(state) = read_u32(*addr) {
                    trace!("{} != STATE_EXEC_FINISH", var);
                    if state == STATE_EXEC_FINISH {
                        finished = true;
                        break;
                    }
                }
            }
        });
        t32::go();
        trace!(
            "Task exec {}",
            if finished { "finished" } else { "not finished" }
        );
        finished
    }

    fn init_state_addr_once(inst: &Inst) {
        INIT_TASK_STATE_ADDR.call_once(|| {
            for t in inst.tasks.iter() {
                let sym = to_task_state_var(&t.id);
                let addr = t32::get_symbol_u32(&sym);
                trace!("Symbol \"{}\", addr {:#x}", sym, addr);
                TASKS_STATE_ADDR.with(|f| {
                    f.borrow_mut().insert(sym, addr);
                });
            }
        });
        trace!("Task state address init ok");
    }

    pub fn wait_task_ready(inst: &Inst) -> Result<(), String> {
        init_state_addr_once(inst);
        trace!("Waiting tasks ...");
        let mut retry = 0;
        loop {
            t32::t32_break();
            let mut result = Ok(());
            let states = TASKS_STATE_ADDR.with(|f| {
                let mut states = Vec::with_capacity(f.borrow().len());
                for (state_var, addr) in f.borrow().iter() {
                    if let Some(value) = t32::read_u32(*addr) {
                        states.push(value)
                    } else {
                        let err = format!("Failed to wait task ready: failed to read variable value, symbol \"{}\", addr {:#x}, from t32",
                                          state_var, addr);
                        warn!("{}", err);
                        result =  Err(err);
                    }
                }
                states
            });
            if result.is_err() {
                return result;
            }
            t32::go();
            if states.iter().any(|state| *state == STATE_TASK_READY) {
                break;
            }
            trace!("Task not ready");
            if retry != 600 {
                sleep(Duration::from_millis(5));
                retry += 1;
            } else {
                warn!("Failed to wait task ready");
                return Err("Failed to wait task ready".into());
            }
        }
        trace!("Task ready");
        Ok(())
    }

    fn to_task_state_var(id: &str) -> String {
        format!("{}_STATE", id)
    }

    thread_local! {
        static DATA_ADDR:RefCell<HashMap<String, u32>> = RefCell::new(HashMap::new());
    }
    static INIT_DATA_ADDR: Once = Once::new();

    fn insert_data_addr(var_name: String) {
        let addr = t32::get_symbol_u32(&var_name);
        trace!("Symbol \"{}\", address {:#x}", var_name, addr);
        DATA_ADDR.with(|s| {
            s.borrow_mut().insert(var_name, addr);
        });
    }

    fn init_data_addr_once(inst: &Inst) {
        INIT_DATA_ADDR.call_once(|| {
            for (hp, _) in inst.hooks.iter_hook() {
                insert_data_addr(hook_var_name(hp).to_string());
            }

            for isr in &inst.isr {
                insert_data_addr(isr_task_var_name(&isr.meta.id));
            }

            for task in &inst.tasks {
                insert_data_addr(isr_task_var_name(&task.id));
            }

            DATA_ADDR.with(|s| {
                s.borrow_mut().shrink_to_fit();
            })
        });
        trace!("Task data variable address inited");
    }

    pub fn write_all(p: &Inst) -> Result<(), String> {
        init_data_addr_once(p);

        t32::t32_break();
        let mut result = Ok(());
        SERIALIZED.with(|s| {
            for (var, val) in s.borrow().iter() {
                let mut addr = 0;
                DATA_ADDR.with(|f| {
                    addr = f.borrow()[var];
                });

                if t32::write(addr, val) != 0 {
                    let err = format!("failed to write test case data to symbol \"{}\"", var);
                    warn!("{}", err);
                    result = Err(err);
                }
            }
        });
        if result.is_ok() {
            t32::go();
            trace!("Test case write OK");
            Ok(())
        } else {
            result
        }
    }

    fn notify_task() -> Result<(), String> {
        t32::t32_break();
        let mut result = Ok(());
        TASKS_STATE_ADDR.with(|s| {
            for (var, addr) in s.borrow().iter() {
                if t32::write(*addr, &STATE_DATA_READY.to_le_bytes()) != 0 {
                    let err = format!("failed to write state to symbol \"{}\"", var);
                    warn!("{}", err);
                    result = Err(err);
                }
            }
        });
        if result.is_ok() {
            t32::go();
            trace!("Task notified");
            Ok(())
        } else {
            result
        }
    }

    thread_local! {
        static OS_STATE_ADDR: Cell<u32> = Cell::new(0);
        static OS_CRASH_INFO_ADDR: Cell<u32> = Cell::new(0);
    }
    static INIT_OS_VAR_ONCE: Once = Once::new();
    const OS_STATE_VAR: &str = "OS_STATE";
    const OS_CRASH_INFO_VAR: &str = "OS_CRASH_INFO";
    const OS_CRASHED: u32 = 1;

    fn init_os_var_addr() {
        INIT_OS_VAR_ONCE.call_once(|| {
            OS_STATE_ADDR.with(|s| {
                (*s).set(t32::get_symbol_u32(OS_STATE_VAR));
            });

            OS_CRASH_INFO_ADDR.with(|s| {
                (*s).set(t32::get_symbol_u32(OS_CRASH_INFO_VAR));
            });
        });
    }

    fn try_collect_crash() -> Option<String> {
        init_os_var_addr();
        trace!("Trying to collect crash");
        let mut addr = 0;
        OS_STATE_ADDR.with(|f| {
            addr = f.get();
        });
        t32::t32_break();
        let os_state = t32::read_u32(addr).unwrap_or(0);
        t32::go();
        trace!("Kernel state: {}", os_state);
        let mut addr = 0;
        OS_CRASH_INFO_ADDR.with(|f| addr = f.get());
        if os_state == OS_CRASHED {
            let mut retry = 0;
            loop {
                // Give some time for kernel to write out dump info.
                sleep(Duration::from_millis(200));
                t32::t32_break();
                if let Some(info) = t32::read_str(addr) {
                    t32::go();
                    return Some(info);
                } else if retry != 100 {
                    retry += 1;
                    t32::go();
                } else {
                    t32::go();
                    warn!("OS_CRASH equals one, but failed to collect crash info, crash info address: {:#x}",addr);
                    return None;
                }
            }
        } else {
            None
        }
    }

    pub fn monitor() -> ExecResult {
        if let Err(e) = notify_task() {
            return ExecResult::Failed(e);
        }
        trace!("Monitoring kernel ...");
        let mut retry = 0;
        loop {
            sleep(Duration::from_millis(50));
            if exec_finished() {
                return ExecResult::Success(Feedback);
            } else if let Some(info) = try_collect_crash() {
                return ExecResult::Crashed(info);
            } else if retry != 200 {
                retry += 1;
            } else {
                return ExecResult::Failed("Time out".to_string());
            }
        }
    }
}

fn script_exec(p: &Inst, cfg: &Config) -> ExecResult {
    let extra = format!("#include\"{}\"", cfg.extra_header);
    let p = to_c(&p, Some(extra));
    write(cfg.template_dir.join(&cfg.out_name), p).unwrap();
    let cmd = cfg.shell_cmd.split_whitespace().collect::<Vec<_>>();
    let mut sub_p = Popen::create(
        &cmd,
        PopenConfig {
            stdin: Redirection::Pipe,
            stdout: Redirection::Pipe,
            stderr: Redirection::Merge,
            ..Default::default()
        },
    )
    .unwrap();

    let mut out = sub_p.stdout.take().unwrap();
    let ret = sub_p.wait_timeout(Duration::new(cfg.timeout, 0)).unwrap();
    sub_p.kill().unwrap();

    if ret == None {
        ExecResult::Failed("Time out".to_string())
    } else {
        let mut result = String::new();
        out.read_to_string(&mut result).unwrap();
        extract_result(result)
    }
}

fn extract_result(info: String) -> ExecResult {
    for line in info.lines() {
        if line.contains("rtkaller:") {
            return match parse_record(line) {
                0 => ExecResult::Success(Feedback),
                1 => ExecResult::Failed(info),
                2 => ExecResult::Crashed(info),
                _ => unreachable!(),
            };
        }
    }
    eprintln!("No communication msg from shell script for rtkaller");
    exit(1)
}

fn parse_record(record: &str) -> u8 {
    let record = record.trim();
    let i = record.find(|c| c == ':').unwrap();
    let record = &record[i + 1..];
    let i = record.find(|c| c == '=').unwrap();
    let key = record[0..i].trim();
    let v = record[i + 1..].trim();
    if key == "result" {
        match v {
            "success" => 0,
            "crashed" => 2,
            _ => 1,
        }
    } else {
        1
    }
}
