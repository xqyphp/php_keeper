#ifndef keeper_rec_h
#define keeper_rec_h

#include "keeper_header.h"

struct keeper_rec_globals
{
	/* data */
	int 	status;
	char* 	rg_cls;
	char* 	rg_func;
	int   	rg_argc;
	zval** 	rg_argv;
};

struct keeper_rec
{
	const char* (*get_request_uri)();
	const char* (*get_request_method)();
	HashTable*  (*get_request_headers)();
	HashTable*  (*get_request_params)();
	HashTable*  (*get_request_cookies)();
	const char* (*get_request_header)(const char* name);
	const char* (*get_request_param)(const char* name);
	const char* (*get_request_cookie)(const char* name);
	const char* (*get_class_name)();
	const char* (*get_function_name)();
	int         (*get_fargc)();
	zval*       (*get_farg)(int index);
};

struct keeper_rec *get_keeper_rec();
int keeper_rec_init();
int keeper_rec_destroy();
int keeper_rec_oncall();

#endif