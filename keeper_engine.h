#ifndef keeper_engine_h
#define keeper_engine_h

#include "zend_llist.h"

#include "keeper_sapi.h"
#include "keeper_setting.h"
#include "keeper_module.h"

struct keeper_engine
{
	struct keeper_sapi    *papi;
	struct keeper_setting *setting;
	struct keeper_modules *modules;
};

struct keeper_engine* get_keeper_engine();

int keeper_engine_startup();
int keeper_engine_shutdown();

int keeper_engine_request_connect();
int keeper_engine_request_disconnect();
int keeper_engine_method_call();

int keeper_engine_register(struct keeper_module* module);
int keeper_engine_unregister(struct keeper_module* module);

#endif