#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

static int PAGE_SIZE = -1;
static CURL* curl = nullptr;

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

		curl = curl_easy_init();
		if (!(curl))
			return 1;

		return 0;
	}

	void c_pexit()
	{
		curl_easy_cleanup(curl);
	}
}

static size_t
write_callback(void* ptr, size_t size, size_t nmb, std::string* data)
{
	data->append((char*) ptr, size * nmb);
	return size * nmb;
}

struct response
{
	const char* s_data;
	size_t s_size;
};

static int prepare_req(struct response* retp, const char* url)
{
	std::string ret;

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret);
	curl_easy_perform(curl);

	size_t rsize = ret.size();
	char* buf = (char*) malloc(rsize + 1);
	if (!(buf))
		return 1;

	memcpy(buf, ret.data(), rsize);
	buf[rsize] = '\0';

	struct response rp = {.s_data = buf, .s_size = rsize};
	*retp = rp;

	return 0;
}

extern "C"
{
	const char* req_get(const char* url)
	{
		struct response ret;
		if (!(prepare_req(&ret, url) == 0))
			return nullptr;

		return ret.s_data;
	}

	void req_free(void* ptr)
	{
		free(ptr);
	}
}