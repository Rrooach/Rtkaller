use bitflags::_core::time::Duration;
use std::ffi::{CStr, CString};
use std::os::raw::{c_char, c_int};
use std::process::exit;
use std::thread::sleep;

pub fn config(node: &str, port: u16) -> c_int {
    let node_key: &CStr =
        unsafe { CStr::from_bytes_with_nul_unchecked(concat!("NODE=", "\0").as_bytes()) };
    let port_key: &CStr =
        unsafe { CStr::from_bytes_with_nul_unchecked(concat!("PORT=", "\0").as_bytes()) };
    let pack_len_key: &CStr =
        unsafe { CStr::from_bytes_with_nul_unchecked(concat!("PACKLEN=", "\0").as_bytes()) };
    let len: &CStr =
        unsafe { CStr::from_bytes_with_nul_unchecked(concat!("1024", "\0").as_bytes()) };

    let node = CString::new(node).unwrap();
    let port = CString::new(port.to_string()).unwrap();
    unsafe {
        let mut ret;
        ret = bindings::T32_Config(node_key.as_ptr(), node.as_ptr());
        if ret != 0 {
            return ret;
        }
        ret = bindings::T32_Config(port_key.as_ptr(), port.as_ptr());
        if ret != 0 {
            return ret;
        }

        bindings::T32_Config(pack_len_key.as_ptr(), len.as_ptr())
    }
}

pub fn init() -> c_int {
    unsafe {
        let mut ret;
        ret = bindings::T32_Init();
        if ret != 0 {
            return ret;
        }

        let mut retry = 0;
        loop {
            ret = bindings::T32_Attach(bindings::T32_DEV_ICD);
            if ret == 0 {
                break;
            } else if retry != 3 {
                sleep(Duration::from_millis(100));
                retry += 1;
            } else {
                return ret;
            }
        }
        bindings::T32_Nop()
    }
}

pub fn t32_exit() -> c_int {
    unsafe { bindings::T32_Exit() }
}

pub fn read_u32(addr: u32) -> Option<u32> {
    let mut val = [0u8; 4];
    let ret = read_memory(addr, &mut val);
    if ret == 0 {
        Some(u32::from_le_bytes(val))
    } else {
        None
    }
}

pub fn get_symbol_u32(sym: &str) -> u32 {
    let c_sym = CString::new(sym).unwrap();
    let mut addr = 0u32;
    let mut _val = 0u32;
    let mut _size = 0u32;

    unsafe {
        if bindings::T32_GetSymbol(c_sym.as_ptr(), &mut addr, &mut _val, &mut _size) != 0 {
            eprintln!("failed to get val of symbol \"{}\" from t32", sym);
            exit(1);
        }
    }

    addr
}

fn success_or_redo<T>(interval: Duration, timeout: Duration, mut f: T) -> c_int
where
    T: FnMut() -> c_int,
{
    let mut waited = Duration::from_millis(0);
    let mut ret = 0;
    while waited <= timeout {
        ret = f();
        if ret == 0 {
            break;
        } else {
            waited += interval;
            sleep(interval);
        }
    }
    ret
}

pub fn read_memory(addr: u32, val: &mut [u8]) -> c_int {
    success_or_redo(
        Duration::from_millis(5),
        Duration::from_millis(10000),
        || unsafe { bindings::T32_ReadMemory(addr, 0, val.as_mut_ptr(), val.len() as c_int) },
    )
}

pub fn write_memory(addr: u32, val: &[u8]) -> c_int {
    success_or_redo(
        Duration::from_millis(5),
        Duration::from_millis(10000),
        || unsafe { bindings::T32_WriteMemory(addr, 0, val.as_ptr(), val.len() as c_int) },
    )
}

pub fn read_str(addr: u32) -> Option<String> {
    let mut buf: [u8; 1024] = [0; 1024];
    let ret = read_memory(addr, &mut buf);
    if ret == 0 {
        unsafe {
            Some(
                CString::from(CStr::from_ptr(buf.as_mut_ptr() as *mut c_char))
                    .to_string_lossy()
                    .into_owned(),
            )
        }
    } else {
        None
    }
}

pub fn write(addr: u32, data: &[u8]) -> i32 {
    write_memory(addr, data)
}

pub fn get_window_content() -> String {
    let window: &CStr =
        unsafe { CStr::from_bytes_with_nul_unchecked(concat!("List", "\0").as_bytes()) };
    let mut content = Vec::new();
    let mut buf: [u8; 1024] = [0; 1024];
    let mut len;
    let mut offset: u32 = 0;
    loop {
        unsafe {
            len = bindings::T32_GetWindowContent(
                window.as_ptr(),
                buf.as_mut_ptr() as *mut c_char,
                1024,
                offset,
                bindings::T32_PRINTCODE_ASCII,
            );
        }
        if len <= 0 {
            break;
        }
        content.extend_from_slice(&buf[0..len as usize]);
        offset += len as u32;
    }
    String::from_utf8(content).unwrap()
}

pub fn execute_command(cmd: &str) -> Result<(), CString> {
    let c_cmd = CString::new(cmd).unwrap();
    let mut buf: [c_char; 1024] = [0; 1024];
    unsafe {
        if bindings::T32_ExecuteCommand(c_cmd.as_ptr(), buf.as_mut_ptr(), 1024) != 0 {
            Err(CString::from(CStr::from_ptr(buf.as_ptr())))
        } else {
            Ok(())
        }
    }
}

pub fn cmd(c: &str) -> Result<(), ()> {
    let c_cmd = CString::new(c).unwrap();
    unsafe {
        if bindings::T32_Cmd(c_cmd.as_ptr()) != 0 {
            Err(())
        } else {
            Ok(())
        }
    }
}

#[derive(Debug)]
pub enum PracticeState {
    NotRunning,
    Running,
    WindowOpen,
}

pub fn get_practice_state() -> Option<PracticeState> {
    let mut state: c_int = 0;
    unsafe {
        if bindings::T32_GetPracticeState(&mut state) != 0 {
            return None;
        }
    }
    use PracticeState::*;
    let state = match state {
        0 => NotRunning,
        1 => Running,
        2 => WindowOpen,
        _ => unreachable!(),
    };
    Some(state)
}

pub fn go() {
    // ignore ret value from t32
    unsafe {
        bindings::T32_Go();
    }
}

pub fn t32_break() {
    unsafe {
        bindings::T32_Break();
    };
}

#[allow(dead_code)]
pub mod bindings {
    use std::os::raw::c_int;

    pub const T32_DEV_OS: c_int = 0;
    pub const T32_DEV_ICD: c_int = 1;
    pub const T32_PRINTCODE_ASCII: u32 = 65;
    pub const T32_PRINTCODE_ASCIIP: u32 = 66;
    pub const T32_PRINTCODE_ASCIIE: u32 = 67;
    pub const T32_PRINTCODE_CSV: u32 = 68;
    pub const T32_PRINTCODE_XML: u32 = 69;

    extern "C" {
        pub fn T32_Config(
            String1: *const ::std::os::raw::c_char,
            String2: *const ::std::os::raw::c_char,
        ) -> ::std::os::raw::c_int;

        pub fn T32_Init() -> ::std::os::raw::c_int;

        pub fn T32_Attach(DeviceSpecifier: ::std::os::raw::c_int) -> ::std::os::raw::c_int;

        pub fn T32_Terminate(ShellReturnValue: ::std::os::raw::c_int) -> ::std::os::raw::c_int;

        pub fn T32_Exit() -> ::std::os::raw::c_int;

        pub fn T32_WriteMemory(
            Address: u32,
            Access: ::std::os::raw::c_int,
            pBuffer: *const u8,
            Size: ::std::os::raw::c_int,
        ) -> ::std::os::raw::c_int;

        pub fn T32_ReadMemory(
            Address: u32,
            Access: ::std::os::raw::c_int,
            pBuffer: *mut u8,
            Size: ::std::os::raw::c_int,
        ) -> ::std::os::raw::c_int;

        pub fn T32_Nop() -> ::std::os::raw::c_int;

        pub fn T32_ResetCPU() -> ::std::os::raw::c_int;

        pub fn T32_GetSymbol(
            SymbolName: *const ::std::os::raw::c_char,
            pAddress: *mut u32,
            pSize: *mut u32,
            pAccess: *mut u32,
        ) -> ::std::os::raw::c_int;

        pub fn T32_WriteVariableValue(
            VariableName: *const ::std::os::raw::c_char,
            ValueLower32Bit: u32,
            ValueUpper32Bit: u32,
        ) -> ::std::os::raw::c_int;

        pub fn T32_ReadVariableValue(
            VariableName: *const ::std::os::raw::c_char,
            pValueLower32Bit: *mut u32,
            pValueUpper32Bit: *mut u32,
        ) -> ::std::os::raw::c_int;

        pub fn T32_GetWindowContent(
            command: *const ::std::os::raw::c_char,
            buffer: *mut ::std::os::raw::c_char,
            requested: u32,
            offset: u32,
            print_code: u32,
        ) -> ::std::os::raw::c_int;

        pub fn T32_Go() -> ::std::os::raw::c_int;

        pub fn T32_WriteRegisterByName(
            regname: *const ::std::os::raw::c_char,
            value: u32,
            hvalue: u32,
        ) -> ::std::os::raw::c_int;

        pub fn T32_ExecuteCommand(
            pCommand: *const ::std::os::raw::c_char,
            pBuffer: *mut ::std::os::raw::c_char,
            BufferSize: u32,
        ) -> c_int;

        pub fn T32_GetPracticeState(pstate: *mut c_int) -> c_int;

        pub fn T32_Break() -> c_int;
        pub fn T32_Cmd(pCommand: *const ::std::os::raw::c_char) -> c_int;
    }
}
