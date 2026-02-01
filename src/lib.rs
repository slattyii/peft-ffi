mod call;
mod ffi;

pub use ffi::*;

#[cfg(test)]
mod tests {
	use std::{
		ffi::{CStr, CString, c_void},
		thread,
	};

	use crate::*;

	#[test]
	fn test() {
		if unsafe { c_handshake() } != 4096 {
			panic!("handshake data mismatch");
		};
		if unsafe { c_pinit() } != 0 {
			panic!("C-side init fail");
		};

		let mut threads = Vec::new();

		for idx in 0..100 {
			let th = thread::spawn(move || {
				let urlp = CString::new("http://localhost:3000").unwrap();
				// let qryp = CString::new("text=hello+world").unwrap();
				let qryp = std::ptr::null();

				let ret = unsafe { req_get(urlp.as_ptr(), qryp) };
				if ret.is_null() {
					println!("got null pointer");
					return;
				};

				let _ = unsafe { CStr::from_ptr(ret) }.to_string_lossy().to_string();

				unsafe {
					req_free(ret as *mut c_void);
				};

				println!("thread {idx} request response data");
			});

			threads.push(th);
		}

		for th in threads {
			th.join().ok();
		}

		unsafe {
			c_pexit();
		}
	}
}
