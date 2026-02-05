// lib.rs
use configparser::ini::Ini;
use std::ffi::CStr;
use std::fs;
use std::path::Path;
use std::ptr;
use std::slice;

#[unsafe(no_mangle)]
pub unsafe extern "C"
fn GetPrivateProfileStringUtf8(
    lpAppName: *const u8,
    lpKeyName: *const u8,
    lpDefault: *const u8,
    lpReturnedString: *mut u8,
    nSize: u32,
    lpFileName: *const u8,
) -> u32 {
    // 安全检查
    if nSize == 0 || lpReturnedString.is_null() {
        return 0;
    }

    // 初始化输出缓冲区为 0（确保 null-terminated）
    unsafe { ptr::write_bytes(lpReturnedString, 0, nSize as usize) };

    // 将 UTF-8 C 字符串转为 &str
    let app_name = unsafe { cstr_to_str(lpAppName) };
    let key_name = unsafe { cstr_to_str(lpKeyName) };
    let default = unsafe { cstr_to_str(lpDefault) };
    let file_name = unsafe { cstr_to_str(lpFileName) };

    // 读取文件（假设文件是 UTF-8 编码）
    let content = match fs::read_to_string(file_name) {
        Ok(c) => c,
        Err(_) => {
            unsafe { write_utf8_truncated(default, lpReturnedString, nSize) };
            return byte_len_without_null(default, nSize);
        }
    };

    // 解析 INI
    let mut config = Ini::new();
    if config.read(content).is_err() {
        unsafe { write_utf8_truncated(default, lpReturnedString, nSize) };
        return byte_len_without_null(default, nSize);
    }

    // 获取值
    let value = config
        .get(app_name, key_name)
        .unwrap_or_else(|| default.to_string());
    unsafe { write_utf8_truncated(&value, lpReturnedString, nSize) };
    byte_len_without_null(&value, nSize)
}

// Helper: 将 *const u8 (null-terminated UTF-8) 转为 &str
unsafe fn cstr_to_str(ptr: *const u8) -> &'static str {
    if ptr.is_null() {
        return "";
    }
    let cstr = unsafe { CStr::from_ptr(ptr as *const i8) }; // safe for UTF-8
    match cstr.to_str() {
        Ok(s) => s,
        Err(_) => "", // invalid UTF-8 → treat as empty
    }
}

// Helper: 安全写入 UTF-8 字符串到缓冲区，自动截断且不破坏 UTF-8
unsafe fn write_utf8_truncated(s: &str, buf: *mut u8, n_size: u32) {
    if n_size == 0 || buf.is_null() {
        return;
    }

    let max_bytes = (n_size - 1) as usize; // reserve 1 byte for \0

    // 找到不超过 max_bytes 的最大合法 UTF-8 边界
    let truncated_bytes = if s.len() <= max_bytes {
        s.as_bytes()
    } else {
        // 向前找到最后一个完整 UTF-8 字符边界
        let mut len = max_bytes;
        while !s.is_char_boundary(len) && len > 0 {
            len -= 1;
        }
        &s.as_bytes()[..len]
    };

    // 写入字节
    unsafe { ptr::copy_nonoverlapping(truncated_bytes.as_ptr(), buf, truncated_bytes.len()) };
    unsafe { *buf.add(truncated_bytes.len()) = 0 }; // null terminator
}

// Helper: 计算实际写入的字节数（不含 \0），受 nSize 限制
fn byte_len_without_null(s: &str, n_size: u32) -> u32 {
    let max_bytes = n_size.saturating_sub(1) as usize;
    if s.len() <= max_bytes {
        s.len() as u32
    } else {
        let mut len = max_bytes;
        while !s.is_char_boundary(len) && len > 0 {
            len -= 1;
        }
        len as u32
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn WritePrivateProfileStringUtf8(
    lpAppName: *const u8,
    lpKeyName: *const u8,
    lpString: *const u8,
    lpFileName: *const u8,
) -> bool {
    // 安全检查：必须提供 app, key, file
    if lpAppName.is_null() || lpKeyName.is_null() || lpFileName.is_null() {
        return false;
    }

    // Helper to convert C string pointer to Rust String
    let cstr_to_string = |ptr: *const u8| -> Option<String> {
        if ptr.is_null() {
            return Some(String::new());
        }
        unsafe {
            CStr::from_ptr(ptr as *const i8)
                .to_str()
                .ok()
                .map(|s| s.to_owned())
        }
    };

    let app_name = match cstr_to_string(lpAppName) {
        Some(s) if !s.is_empty() => s,
        _ => return false, // App name must be non-empty
    };
    let key = match cstr_to_string(lpKeyName) {
        Some(s) if !s.is_empty() => s,
        _ => return false, // Key must be non-empty
    };
    let file_name = match cstr_to_string(lpFileName) {
        Some(s) if !s.is_empty() => s,
        _ => return false,
    };

    // lpString can be null or empty → treat as empty string (valid value)
    let value = cstr_to_string(lpString).unwrap_or_default();

    // Load existing config or start fresh
    let mut config = Ini::new();
    match fs::read_to_string(&file_name) {
        Ok(content) => {
            if let Err(_) = config.read(content) {
                // If file exists but is malformed, fail (don't overwrite!)
                return false;
            }
        }
        Err(e) if e.kind() == std::io::ErrorKind::NotFound => {
            // File doesn't exist → OK, create new
        }
        Err(_) => {
            // Other I/O error (permission, etc.) → fail
            return false;
        }
    }

    // Set the key-value pair
    config.set(&app_name, &key, Some(value));

    // Ensure parent directory exists
    if let Some(parent) = Path::new(&file_name).parent() {
        if let Err(_) = fs::create_dir_all(parent) {
            return false;
        }
    }

    // Write back to file
    if config.write(&file_name).is_err() {
        return false;
    }

    true
}


// #[unsafe(no_mangle)]
// pub unsafe extern "C" fn GetPrivateProfileIntUtf8(
//     lpAppName: *const u8,
//     lpKeyName: *const u8,
//     nDefault: i32,
//     lpFileName: *const u8,
// ) -> i32 {
//     // 安全检查
//     if lpAppName.is_null() || lpKeyName.is_null() || lpFileName.is_null() {
//         return nDefault;
//     }
//     let app_name = unsafe { cstr_to_str(lpAppName) };
    

    
// }