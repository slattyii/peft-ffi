use std::fs;

fn main() {
	let mut build = cc::Build::new();

	let entrs = fs::read_dir("./src/ffi").expect("ffi dir not found");

	for entr in entrs.flatten() {
		let p = entr.path();
		if p.extension().map_or(false, |s| s == "cc") {
			build.file(p);
		}
	}

	build.compile("peft_ffi");

	println!("cargo:rerun-if-changed=src/ffi");
	println!("cargo:rustc-link-lib=curl");
	println!("cargo:rustc-link-lib=stdc++");
}
