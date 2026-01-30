mod call;
mod ffi;

#[unsafe(no_mangle)]
pub extern "C" fn r_handshake() -> i32 {
	4096
}

unsafe extern "C" {
	pub unsafe fn c_handshake() -> i32;
	pub unsafe fn c_pinit() -> i32;
}

#[cfg(test)]
mod tests {
	use super::*;

	#[test]
	fn test() {
		if unsafe { c_handshake() } != 4096 {
			panic!("handshake data missmatch");
		};
		if unsafe { c_pinit() } != 0 {
			panic!("C-side init fail");
		}

		println!("ok");
	}
}
