#include "include/reqter.hh"

#include <cstring>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

static CURL* curlp = nullptr;

int reqter_init()
{
	if (!(curl_global_init(CURL_GLOBAL_DEFAULT) == 0))
		return 1;
	curlp = curl_easy_init();
	if (!(curlp))
		return 2;

	return 0;
}

void reqter_exit()
{
	curl_easy_cleanup(curlp);
	curl_global_cleanup();
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

	CURL* curl = curl_easy_duphandle(curlp);
	curl_easy_reset(curl);

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret);
	CURLcode code = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	if (!(code == CURLE_OK))
		return code;

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