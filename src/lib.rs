mod ffi;

pub mod pffi {
	use super::ffi::*;

	#[unsafe(no_mangle)]
	pub extern "C" fn r_handshake() -> i32 {
		0x2
	}

	unsafe extern "C" {
		pub unsafe fn c_handshake() -> i32;
	}
}

#[cfg(test)]
mod tests {
	use super::*;

	#[test]
	fn test() {
		unsafe {
			println!("c handshake: {}", pffi::c_handshake());
		}
	}
}
