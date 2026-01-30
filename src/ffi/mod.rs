use std::ffi::c_void;

#[unsafe(no_mangle)]
pub extern "C" fn r_handshake() -> i32 {
	4096
}

unsafe extern "C" {
	pub unsafe fn c_handshake() -> i32;
	pub unsafe fn c_pinit() -> i32;
}
