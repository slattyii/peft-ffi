use std::ffi::{c_char, c_void};

#[unsafe(no_mangle)]
pub extern "C" fn r_handshake() -> i32 {
	4096
}

unsafe extern "C" {
	pub unsafe fn c_handshake() -> i32;
	pub unsafe fn c_pinit() -> i32;
	pub unsafe fn c_pexit();

	pub unsafe fn req_get(url: *const c_char, query: *const c_char) -> *const c_char;
	pub unsafe fn req_free(ptr: *mut c_void);
}
