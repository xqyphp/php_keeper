#ifndef keeper_module_h
#define keeper_module_h
#include "keeper_header.h"
#include "keeper_rec.h"


struct keeper_module
{
	int (*on_enter)(void* data);
	int (*on_call)(void* data);
	int (*on_leave)(void* data);
};

struct keeper_modules
{
	zend_llist             mod_list;
	llist_dtor_func_t      mod_dtor;
};

struct keeper_modules* get_keeper_modules();

int keeper_modules_init(struct keeper_modules *modules);
int keeper_modules_destroy(struct keeper_modules* modules);

int keeper_modules_onenter(struct keeper_modules* modules,struct keeper_rec* rec);
int keeper_modules_oncall(struct keeper_modules* modules,struct keeper_rec* rec);
int keeper_modules_onleave(struct keeper_modules* modules,struct keeper_rec* rec);

int keeper_modules_add(struct keeper_modules* modules,struct keeper_module* module);
int keeper_modules_del(struct keeper_modules* modules,struct keeper_module* module);
#endif