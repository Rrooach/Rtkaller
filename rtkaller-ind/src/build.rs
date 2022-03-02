// Copyright 2021, Developed by Tsinghua Wingtecher Lab and Shumuyulin Ltd, All rights reserved.
use std::env;
use std::process::exit;

fn main() {
    println!("cargo:rerun-if-change=build.rs");
    if cfg!(feature = "t32") {
        if env::var("CARGO_CFG_WINDOWS").is_ok()
            && &env::var("CARGO_CFG_TARGET_ENV").unwrap() == "gnu"
        {
            let arch = env::var("CARGO_CFG_TARGET_ARCH").unwrap();
            if &arch == "x86" {
                println!("cargo:rustc-link-lib=dylib=t32api");
                println!("cargo:rustc-link-search=native=./t32");
            } else if &arch == "x86_64" {
                println!("cargo:rustc-link-lib=dylib=t32api64");
                println!("cargo:rustc-link-search=native=./t32");
            } else {
                eprintln!("No support for {}-pc-windows-gnu because gnu toolchain report internal error while compiling t32 lib",arch);
                exit(1)
            }
        } else {
            cc::Build::new()
                .file("t32/hlinknet.c")
                .file("t32/hremote.c")
                .include("t32")
                .flag_if_supported("-O2")
                .flag_if_supported("-fPID")
                .flag_if_supported("-g")
                .compile("t32");

            println!("cargo:rustc-link-lib=t32");
        }
    }
}
