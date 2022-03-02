use rustyline::completion::{Completer, FilenameCompleter, Pair};
use rustyline::error::ReadlineError;
use rustyline::highlight::Highlighter;
use rustyline::hint::{Hinter, HistoryHinter};
use rustyline::line_buffer::LineBuffer;
use rustyline::validate::Validator;
use rustyline::Helper;
use rustyline::{Context, Editor, Result};
use std::env::args;
use std::process::exit;
use rtkaller::t32::bindings;
use rtkaller::t32::*;

pub struct T32Helper {
    hinter: HistoryHinter,
    completer: FilenameCompleter,
}

impl Validator for T32Helper {}

impl Highlighter for T32Helper {}

impl Helper for T32Helper {}

impl T32Helper {
    pub fn new() -> Self {
        Self {
            hinter: HistoryHinter {},
            completer: Default::default(),
        }
    }
}

impl Default for T32Helper {
    fn default() -> Self {
        T32Helper::new()
    }
}

impl Hinter for T32Helper {
    fn hint(&self, line: &str, pos: usize, ctx: &Context<'_>) -> Option<String> {
        self.hinter.hint(line, pos, ctx)
    }
}

impl Completer for T32Helper {
    type Candidate = Pair;

    fn complete(
        &self,
        line: &str,
        pos: usize,
        ctx: &Context<'_>,
    ) -> Result<(usize, Vec<Self::Candidate>)> {
        self.completer.complete(line, pos, ctx)
    }

    fn update(&self, line: &mut LineBuffer, start: usize, elected: &str) {
        self.completer.update(line, start, elected)
    }
}

fn main() {
    let args = args().skip(1).collect::<Vec<_>>();
    let (host, port) = if args.is_empty() {
        ("localhost", 20000)
    } else if args.len() == 2 {
        (
            args[0].as_str(),
            args[1].parse::<u16>().unwrap_or_else(|e| {
                eprintln!(
                    "Error: parse error: failed parse \"{}\" as port number: {}",
                    args[1], e
                );
                exit(1)
            }),
        )
    } else {
        eprintln!("Error: input error\n \tusage: t32 [addr] [port]");
        exit(1)
    };

    println!("Init ...");
    if config(host, port) != 0 || init() != 0 {
        eprintln!("Failed to connect to t32, host localhost, port 20000");
        exit(1);
    }

    println!("Connection OK");

    let mut rl = Editor::new();
    rl.set_helper(Some(T32Helper::new()));
    let mut api;
    loop {
        match rl.readline(">>") {
            Ok(line) => {
                rl.add_history_entry(&line);
                api = line;
            }
            Err(ReadlineError::Interrupted) | Err(ReadlineError::Eof) => {
                t32_exit();
                println!("Bye ^_^");
                exit(0);
            }
            Err(e) => {
                t32_exit();
                eprintln!("Input Error: {}", e);
                exit(1);
            }
        }

        let api = api
            .trim()
            .split_whitespace()
            .map(|s| s.trim())
            .collect::<Vec<_>>();
        if api.is_empty() {
            continue;
        }

        match &api[0][..] {
            "go" => println!("ret: {}", unsafe { bindings::T32_Go() }),
            "break" => println!("ret: {}", unsafe { bindings::T32_Break() }),
            "get_symbol_u32" => {
                if api.len() != 2 {
                    eprintln!("Error: usage error: get_symbol_u32 addr");
                    continue;
                }
                let sym = &api[1];
                println!("ret: {}", get_symbol_u32(sym))
            }
            "read_u32" => {
                if api.len() != 2 {
                    eprintln!("Error: usage error: read_u32 addr");
                    continue;
                }
                let addr = if let Ok(addr) = api[1].parse::<u32>() {
                    addr
                } else {
                    eprintln!(
                        "Error: parse error: failed to parse \"{}\" as an integer",
                        api[1]
                    );
                    continue;
                };
                println!("ret: {:?}", read_u32(addr))
            }
            "get_practice_state" => println!("ret: {:?}", get_practice_state()),
            "execute_command" => {
                if api.len() == 1 {
                    eprintln!("Error: usage error: execute_command [command]");
                    continue;
                }
                let args = join(&api[1..]);
                println!("ret: {:?}", execute_command(args.trim()));
            }
            "cmd" => {
                if api.len() == 1 {
                    eprintln!("Error: usage error: cmd [command]");
                    continue;
                }
                let args = join(&api[1..]);
                println!("ret: {:?}", cmd(args.trim()));
            }
            "quit" => {
                println!("Bye ^_^");
                t32_exit();
                break;
            }

            "help" => {
                println!(
                    "Supported command: go, break, get_symbol_u32, read_u32, get_practice_state, execute_command, cmd"
                );
            }

            _ => {
                eprintln!("Error: unsupported command");
                println!(
                    "Supported command: go, break, get_symbol_u32, read_u32, get_practice_state, execute_command, cmd"
                );
            }
        }
    }
}

fn join(args: &[&str]) -> String {
    let mut result = String::new();
    for arg in args.iter().map(|x| x.trim()) {
        result += arg;
        result += " ";
    }
    result
}
