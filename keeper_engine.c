#include "keeper_engine.h"
#include "keeper_rec.h"

static struct keeper_engine g_keeper_engine;

struct keeper_engine* get_keeper_engine()
{
	return &g_keeper_engine;
}

int keeper_engine_startup()
{
	struct keeper_sapi* sapi = get_keeper_sapi();
	sapi->register_handlers();
	sapi->register_overrides();
	g_keeper_engine.papi = sapi;
	g_keeper_engine.setting = sapi->load_setting();
	g_keeper_engine.modules = get_keeper_modules();
	keeper_modules_init(g_keeper_engine.modules);
	return SUCCESS;
}
int keeper_engine_shutdown()
{
	struct keeper_sapi* sapi = get_keeper_sapi();
	sapi->unregister_handlers();
	sapi->unregister_overrides();
	return keeper_modules_destroy(g_keeper_engine.modules);
}

int keeper_engine_request_connect()
{
	struct keeper_rec* rec = get_keeper_rec();
	keeper_rec_init();
	return keeper_modules_onenter(g_keeper_engine.modules,rec);
}

int keeper_engine_request_disconnect()
{
	struct keeper_rec* rec = get_keeper_rec();
	keeper_modules_onleave(g_keeper_engine.modules,rec);
	keeper_rec_destroy();
	return SUCCESS;
}

int keeper_engine_method_call()
{
	struct keeper_rec* rec = get_keeper_rec();
	keeper_rec_oncall();
	return keeper_modules_oncall(g_keeper_engine.modules,rec);
}

int keeper_engine_register(struct keeper_module* module)
{
	return keeper_modules_add(g_keeper_engine.modules,module);
}

int keeper_engine_unregister(struct keeper_module* module)
{
	return keeper_modules_del(g_keeper_engine.modules,module);
}
