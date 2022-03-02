// Copyright 2021, Developed by Tsinghua Wingtecher Lab and Shumuyulin Ltd, All rights reserved.
use std::path::PathBuf;
use std::process::exit;
use structopt::StructOpt;
use rtkaller::primitives::{POSSIBLE_SIZE, REG_SIZE};
use rtkaller::{fuzz, init, parse_app_config, Config};

#[derive(Debug, StructOpt)]
#[structopt(name = "rtkaller", about = env!("CARGO_PKG_DESCRIPTION"), author = env!("CARGO_PKG_AUTHORS"), version =  env!("CARGO_PKG_VERSION"))]
struct Settings {
    /// Size of register, eg.8,16,32,64.
    #[structopt(long, default_value = "32")]
    reg_size: u8,

    /// Extra C header to be included.
    #[structopt(short, long, default_value = "ee.h")]
    custom_header: String,

    /// Shell command of build and run test case
    #[cfg(not(feature = "t32"))]
    #[structopt(short, long)]
    shell_cmd: String,

    /// Directory of template project.
    #[cfg(not(feature = "t32"))]
    #[structopt(short, long)]
    template_dir: PathBuf,

    /// Output name of generated test case.
    #[structopt(short, long, default_value = "rtkaller.c")]
    out_name: String,

    /// Number of test cased to be persisted.
    #[structopt(short, long, default_value = "64")]
    num_save: usize,

    /// Timeout duration for each test case execution.
    #[structopt(short, long, default_value = "30")]
    exec_timeout: u64,

    /// Path to application config file(json format).
    #[structopt(short, long)]
    app_config_path: Option<PathBuf>,

    /// Use external script to execute test case instead of t32.
    #[cfg(feature = "t32")]
    #[structopt(short, long)]
    use_script: bool,

    /// Defines on which host the TRACE32 display driver runs.
    #[cfg(feature = "t32")]
    #[structopt(long, default_value = "localhost")]
    t32_node: String,

    /// Defines the UDP port for sending.
    #[cfg(feature = "t32")]
    #[structopt(long, default_value = "20000")]
    t32_port: u16,

    /// Shell command of build and run test case
    #[cfg(feature = "t32")]
    #[structopt(short, long, default_value = "")]
    shell_cmd: String,

    /// Directory of template project.
    #[cfg(feature = "t32")]
    #[structopt(short, long, default_value = "")]
    template_dir: PathBuf,

    #[cfg(feature = "t32")]
    #[structopt(short, long)]
    restart_os_cmm_hook: String,
}

fn main() {
    let settings = Settings::from_args();

    if !POSSIBLE_SIZE.contains(&settings.reg_size) {
        eprintln!(
            "Error: invalid size of register {}, valid values are {:?}",
            settings.reg_size, POSSIBLE_SIZE
        );
        exit(1)
    }
    REG_SIZE.with(|s| s.set(settings.reg_size));

    #[cfg(feature = "t32")]
    if settings.use_script && settings.shell_cmd.is_empty() {
        eprintln!("Error: shell command must be provided if use_script is set");
        exit(1);
    }

    let app = if let Some(p) = settings.app_config_path {
        parse_app_config(&p)
    } else {
        Default::default()
    };

    let cfg = Config {
        extra_header: settings.custom_header,
        shell_cmd: settings.shell_cmd,
        template_dir: settings.template_dir,
        out_name: settings.out_name,
        num_save: settings.num_save,
        timeout: settings.exec_timeout,
        app,
        #[cfg(feature = "t32")]
        use_script: settings.use_script,
        #[cfg(feature = "t32")]
        t32_node: settings.t32_node,
        #[cfg(feature = "t32")]
        t32_port: settings.t32_port,
        #[cfg(feature = "t32")]
        restart_os_cmm_hook: settings.restart_os_cmm_hook,
    };

    init(&cfg);
    fuzz(cfg)
}
