mod call;
mod ffi;

pub use ffi::*;

#[cfg(test)]
mod tests {
	use std::ffi::{CStr, CString, c_void};

	use crate::*;

	#[test]
	fn test() {
		if unsafe { c_handshake() } != 4096 {
			panic!("handshake data mismatch");
		};
		if unsafe { c_pinit() } != 0 {
			panic!("C-side init fail");
		};

		let urlp = CString::new("https://api.simsimi.vn/v1/simtalk").unwrap();
		let qryp = CString::new("text=hello+world").unwrap();

		let ret = unsafe { req_get(urlp.as_ptr(), qryp.as_ptr()) };
		if ret.is_null() {
			println!("got null pointer");
			return;
		};

		let str = unsafe { CStr::from_ptr(ret) }.to_string_lossy().to_string();

		unsafe {
			req_free(ret as *mut c_void);
		};

		println!("request response data: {}", str);

		unsafe {
			c_pexit();
		}
	}
}
