#ifndef keeper_sapi_h
#define keeper_sapi_h

#include "keeper_setting.h"

struct keeper_sapi
{
	int (*register_handlers)();
	int (*unregister_handlers)();
	int (*register_overrides)();
	int (*unregister_overrides)();
	struct keeper_setting* (*load_setting)();
	int (*reload_setting)();
	int (*http_forbidden)();
};

struct keeper_sapi* get_keeper_sapi();

#endif