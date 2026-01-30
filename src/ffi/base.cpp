#include <cstdlib>
#include <iostream>

static int PAGE_SIZE = -1;

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
		if (PAGE_SIZE < 1)
			return 1;

		return 0;
	}
}