#include "include/reqter.hh"

#include <cstdlib>
#include <curl/curl.h>
#include <curl/easy.h>

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
		if (PAGE_SIZE < 1)
			return 1;

		if (!(reqter_init() == 0))
			return 1;

		return 0;
	}

	void c_pexit()
	{
		reqter_exit();
	}
}

extern "C"
{
	const char* req_get(const char* url)
	{
		struct reqponse_t ret;
		if (!(reqter_prepare(&ret, url) == 0))
			return nullptr;

		return ret.s_data;
	}

	void req_free(void* ptr)
	{
		free(ptr);
	}
}