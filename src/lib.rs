mod call;
mod ffi;

pub use ffi::*;

#[cfg(test)]
mod tests {
	use crate::*;

	#[test]
	fn test() {
		if unsafe { c_handshake() } != 4096 {
			panic!("handshake data mismatch");
		};
		if unsafe { c_pinit() } != 0 {
			panic!("C-side init fail");
		}

		println!("ok");
	}
}
