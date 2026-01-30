#ifndef REQTER_H
#define REQTER_H

#include <curl/curl.h>

struct reqponse_t
{
	const char* s_data;
	size_t s_size;
};

int reqter_init();
void reqter_exit();

int reqter_prepare(struct reqponse_t* retp, const char* url);

#endif