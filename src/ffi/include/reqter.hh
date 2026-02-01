#ifndef REQTER_HH
#define REQTER_HH

#include <curl/curl.h>
#include <curl/easy.h>

#ifdef __cplusplus
extern "C"
{
#endif

	enum request_method
	{
		REQUEST_GET,
		REQUEST_POST
	};

	struct reqponse_t
	{
		char* s_data;
		size_t s_size;
	};
	struct request_t
	{
		request_method rq_med;
		const char* rq_query;
	};

	int reqter_init();
	void reqter_exit();

	int reqter_prepare(
		struct reqponse_t* retp,
		struct request_t* reqt,
		const char* url);

	int reqter_send(
		struct request_t* reqp,
		struct reqponse_t* retp,
		const char* url);

#ifdef __cplusplus
};
#endif

#endif