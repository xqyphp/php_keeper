#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "keeper_engine.h"
#include "keeper_rec.h"

static keeper_engine g_keeper_engine;

struct keeper_engine* get_keeper_engine()
{
	return &get_keeper_engine;
}

int keeper_engine_startup()
{
	g_keeper_engine->papi = get_keeper_sapi();
	g_keeper_engine->setting = papi->load_setting();
	g_keeper_engine->modules = get_keeper_modules();
	keeper_modules_init(g_keeper_engine->modules);
	return SUCCESS;
}
int keeper_engine_shutdown()
{
	return keeper_modules_destroy(g_security_engine->modules);
}

int keeper_engine_request_connect(struct keeper_rec* rec)
{
	keeper_rec_init(rec);
	return keeper_modules_onenter(g_security_engine->modules,rec);
}

int keeper_engine_request_disconnect(struct keeper_rec* rec)
{
	keeper_modules_onleave(g_security_engine->modules,rec);
	keeper_rec_destroy(rec);
	return SUCCESS;
}

int keeper_engine_method_call(struct keeper_rec* rec)
{
	keeper_rec_oncall(rec);
	return keeper_modules_oncall(g_security_engine->modules,rec);
}

int keeper_engine_register(struct keeper_module* module)
{
	return keeper_modules_add(g_security_engine->modules,module);
}

int keeper_engine_unregister(struct keeper_module* module)
{
	return keeper_modules_del(g_security_engine->modules,module);
}
