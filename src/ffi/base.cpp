#include <iostream>

extern "C"
{
	int r_handshake();

	int c_handshake() {
		return 0x1;
	}; 
}