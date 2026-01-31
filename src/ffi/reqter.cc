#include "include/reqter.hh"

#include <cstddef>
#include <cstdio>
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

int reqter_prepare(
	struct reqponse_t* retp,
	struct request_t* reqp,
	const char* url)
{
	std::string ret;

	CURL* curl = curl_easy_duphandle(curlp);
	curl_easy_reset(curl);

	if (!(reqp->rq_query == nullptr))
	{
		size_t urllen = strlen(url);
		size_t qrylen = strlen(reqp->rq_query);
		size_t buflen = urllen + qrylen + 1; // 1 for ?

		char buf[buflen + 1];
		snprintf(buf, sizeof(buf), "%s?%s", url, reqp->rq_query);

		curl_easy_setopt(curl, CURLOPT_URL, buf);

		printf("%s\n", buf);
	}
	else
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
	}

	if (reqp->rq_med == REQUEST_POST)
		curl_easy_setopt(curl, CURLOPT_POST, 1L);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret);

	CURLcode code = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	if (!(code == CURLE_OK))
		return code;

	size_t rsize = ret.size();
	if (rsize <= 0)
		return 1;

	char* buf = (char*) malloc(rsize + 1);
	if (!(buf))
		return 2;

	printf("allocated %db mem for req\n", (int) rsize + 1);

	memcpy(buf, ret.data(), rsize);
	buf[rsize] = '\0';

	struct reqponse_t rp = {.s_data = buf, .s_size = rsize};
	*retp = rp;

	return 0;
}

int reqter_send(
	struct request_t* reqp,
	struct reqponse_t* retp,
	const char* url)
{
	return reqter_prepare(retp, reqp, url);
}