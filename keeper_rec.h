#ifndef keeper_rec
#define keeper_rec

#include "php.h"

struct keeper_rec
{
	const char* (*get_request_line)();
	const char* (*get_method)();
	const char* (*get_header)(const char* name);
	const char* (*get_params)(const char* name);
	const char* (*get_cookie)(const char* name);
	const char* (*get_call_nname)();
	const char* (*get_call_fname)();
	int         (*get_params_count)();
	zval        (*get_param)(int index);
};

struct keeper_rec* get_keeper_rec();

int keeper_rec_init(struct keeper_rec* rec);
int keeper_rec_destroy(struct keeper_rec* rec);
int keeper_rec_oncall(struct keeper_rec* rec);

#endif