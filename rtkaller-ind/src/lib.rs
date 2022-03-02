// Copyright 2021, Developed by Tsinghua Wingtecher Lab and Shumuyulin Ltd, All rights reserved.
#[macro_use]
extern crate bitflags;
#[macro_use]
extern crate log;
#[cfg(feature = "t32")]
#[macro_use]
extern crate lazy_static;
#[cfg(feature = "t32")]
#[macro_use]
extern crate maplit;

use crate::exec::{exec, ExecResult};
use crate::model::APPConfig;
use crate::prog::Inst;
use crate::translate::to_c;
use std::collections::VecDeque;
use std::fs::{create_dir_all, write, File};
use std::io::ErrorKind;
use std::path::{Path, PathBuf};
use std::process::exit;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::{Arc, Mutex};
use std::thread::{sleep, spawn};
use std::time::Duration;

pub mod exec;
pub mod gen;
pub mod model;
pub mod primitives;
pub mod prog;
#[cfg(feature = "t32")]
pub mod t32;
pub mod translate;

struct Stats {
    crashed: AtomicUsize,
    failed: AtomicUsize,
    executed: AtomicUsize,
}

impl Stats {
    pub fn new() -> Self {
        Self {
            crashed: AtomicUsize::new(0),
            failed: AtomicUsize::new(0),
            executed: AtomicUsize::new(0),
        }
    }

    pub fn inc_exec(&self) -> usize {
        self.executed.fetch_add(1, Ordering::SeqCst)
    }

    pub fn inc_failed(&self) -> usize {
        self.failed.fetch_add(1, Ordering::SeqCst)
    }

    pub fn inc_crashed(&self) -> usize {
        self.crashed.fetch_add(1, Ordering::SeqCst)
    }

    pub fn exec(&self) -> usize {
        self.executed.load(Ordering::SeqCst)
    }

    pub fn failed(&self) -> usize {
        self.failed.load(Ordering::SeqCst)
    }

    pub fn crashed(&self) -> usize {
        self.crashed.load(Ordering::SeqCst)
    }
}

#[derive(Debug, Clone)]
pub struct Config {
    pub extra_header: String,
    pub shell_cmd: String,
    pub template_dir: PathBuf,
    pub out_name: String,
    pub num_save: usize,
    pub timeout: u64,
    pub app: APPConfig,
    #[cfg(feature = "t32")]
    pub use_script: bool,
    #[cfg(feature = "t32")]
    pub t32_node: String,
    #[cfg(feature = "t32")]
    pub t32_port: u16,
    #[cfg(feature = "t32")]
    pub restart_os_cmm_hook: String,
}

struct State {
    // crashes: Vec<String>,
    // failed: VecDeque<String>,
    executed: Mutex<VecDeque<Inst>>,
}

impl State {
    pub fn with_capacity(size: usize) -> Self {
        Self {
            // crashes: Default::default(),
            // failed: Default::default(),
            executed: Mutex::new(VecDeque::with_capacity(size)),
        }
    }

    pub fn insert_exec(&self, exec: Inst) {
        let mut g = self.executed.lock().unwrap();
        if g.len() == g.capacity() {
            g.pop_front();
        }
        g.push_back(exec)
    }
}

pub fn fuzz(cfg: Config) {
    let stats = Arc::new(Stats::new());
    sample_stats(stats.clone());
    let state = Arc::new(State::with_capacity(cfg.num_save));
    set_ctrl_c(state.clone(), cfg.clone());

    loop {
        let case = gen::gen(&cfg.app);
        let ret = exec(&case, &cfg);

        match ret {
            ExecResult::Success(_) => {
                state.insert_exec(case);
                stats.inc_exec();
            }
            ExecResult::Failed(reason) => {
                let extra = format!("#include\"{}\"", cfg.extra_header);
                let p = to_c(&case, Some(extra));
                save("failed", &p, &reason, stats.failed());
                stats.inc_failed();
            }
            ExecResult::Crashed(info) => {
                let extra = format!("#include\"{}\"", cfg.extra_header);
                let p = to_c(&case, Some(extra));
                warn!("============= Crashed =============");
                warn!("{}", info);
                warn!("============= Caused by ==============");
                warn!("{}", p);

                save("crashed", &p, &info, stats.crashed());
                stats.inc_crashed();
            }
        }
    }
}
#[cfg(feature = "t32")]
use crate::t32::t32_exit;

fn set_ctrl_c(state: Arc<State>, cfg: Config) {
    ctrlc::set_handler(move || {
        warn!("Ctrl-C received, persisting ...");
        let exec_dir = Path::new("exec");
        create_if_not_exist(exec_dir);
        let extra = format!("#include\"{}\"", cfg.extra_header);

        {
            let cases = state.executed.lock().unwrap();
            for (i, c) in cases.iter().enumerate() {
                let name = format!("case_{}", i);
                let c = to_c(c, Some(extra.clone()));
                write(exec_dir.join(name), c).unwrap();
            }
        }
        #[cfg(feature = "t32")]
        t32::t32_exit();
        info!("All done");
        exit(0)
    })
    .expect("Error setting Ctrl-C handler");
}

fn save<T: AsRef<Path>>(base_dir: T, p: &str, reason: &str, index: usize) {
    let dig = md5::compute(reason);
    let name = format!("{:x}", dig);
    let base_dir = base_dir.as_ref();
    let dir = base_dir.join(&name);
    create_if_not_exist(&dir);

    write(dir.join("reason"), reason).unwrap();
    write(dir.join(format!("p{}", index)), p).unwrap();
}

fn create_if_not_exist(dir: &Path) {
    if let Err(e) = create_dir_all(&dir) {
        if e.kind() != ErrorKind::AlreadyExists {
            eprintln!("Fail to create dir {}: {}", dir.display(), e);
            exit(1);
        }
    }
}

fn sample_stats(stats: Arc<Stats>) {
    spawn(move || loop {
        sleep(Duration::new(10, 0));
        let exec = stats.exec();
        let failed = stats.failed();
        let crashed = stats.crashed();

        info!("normal {}, failed {}, crashed {}.", exec, failed, crashed);
    });
}

fn show_logo() {
    const LOGO: &str = r"RTKALLER";

    println!("{}", LOGO);
}

pub fn init(cfg: &Config) {
    #[allow(clippy::collapsible_if)]
    #[cfg(feature = "t32")]
    if cfg.use_script {
        if !cfg.template_dir.exists() {
            eprintln!(
                "Error: template project dir [{}] does not exist.",
                cfg.template_dir.display()
            );
            exit(1);
        }
    } else {
        use std::panic::set_hook;
        if t32::config(&cfg.t32_node, cfg.t32_port) != 0 || t32::init() != 0 {
            eprintln!(
                "Error: failed to init t32: node={} port={}",
                cfg.t32_node, cfg.t32_port
            );
            exit(1);
        }
        set_hook(Box::new(|_| {
            t32_exit();
        }));
    }

    #[cfg(not(feature = "t32"))]
    if !cfg.template_dir.exists() {
        eprintln!(
            "Error: template project dir [{}] does not exist.",
            cfg.template_dir.display()
        );
        exit(1);
    }

    create_if_not_exist(Path::new("failed"));
    create_if_not_exist(Path::new("crashed"));
    pretty_env_logger::init_timed();

    show_logo();
}

pub fn parse_app_config(f: &Path) -> APPConfig {
    let cfg_file = File::open(f).unwrap_or_else(|e| {
        eprintln!("failed to open app config file \"{}\": {}", f.display(), e);
        exit(1)
    });
    serde_json::from_reader(cfg_file).unwrap_or_else(|e| {
        eprintln!("failed to parse app config file \"{}\": {}", f.display(), e);
        exit(1)
    })
}
