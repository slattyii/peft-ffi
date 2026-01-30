#include <iostream>

static int PAGE_SIZE;

extern "C"
{
	int r_handshake();
	int c_handshake()
	{
		PAGE_SIZE = r_handshake();
		return PAGE_SIZE;
	}

	int c_pinit()
	{
		// chuẩn bị ở đây
		return 0;
	}
}