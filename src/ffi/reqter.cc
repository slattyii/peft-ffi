#include "include/reqter.hh"

#include <cstring>
#include <curl/easy.h>
#include <string>

static CURL* curlp = nullptr;

int reqter_init()
{
	curlp = curl_easy_init();
	if (!(curlp))
		return 1;

	return 0;
}

void reqter_exit()
{
	curl_easy_cleanup(curlp);
}

static size_t
write_callback(void* ptr, size_t size, size_t nmb, std::string* data)
{
	data->append((char*) ptr, size * nmb);
	return size * nmb;
}

int reqter_prepare(struct reqponse_t* retp, const char* url)
{
	std::string ret;

	curl_easy_setopt(curlp, CURLOPT_URL, url);
	curl_easy_setopt(curlp, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curlp, CURLOPT_WRITEDATA, &ret);
	curl_easy_perform(curlp);

	size_t rsize = ret.size();
	char* buf = (char*) malloc(rsize + 1);
	if (!(buf))
		return 1;

	memcpy(buf, ret.data(), rsize);
	buf[rsize] = '\0';

	struct reqponse_t rp = {.s_data = buf, .s_size = rsize};
	*retp = rp;

	return 0;
}