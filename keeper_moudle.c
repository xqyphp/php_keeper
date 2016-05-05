#include "keeper_moudle.h"
#include "keeper_defs.h"


static keeper_modules g_keeper_modules;


struct keeper_modules* get_keeper_modules()
{
	return &g_keeper_modules;
}

#define DO_MOD_FILTER(ret_val) \
	switch(ret_val){\
			case pr_pass:\
			case pr_next:\
				continue;\
			case pr_return:\
				return -1;\
	}

static void keeper_module_dtor(void* data)
{

}

int keeper_modules_init(struct keeper_modules *modules)
{
	modules->mod_dtor = keeper_module_dtor;
	zend_llist_init(modules->mod_list,sizeof(keeper_moudle),keeper_module_dtor,1);
	return SUCCESS;
}

int keeper_modules_destroy(struct keeper_modules* modules)
{
	zend_llist_clean(modules->mod_list);
	return SUCCESS;
}

int keeper_modules_add(struct keeper_modules* modules,struct keeper_module* module)
{
	zend_llist_add_element(modules->mod_list,module);
	return SUCCESS;
}

int keeper_modules_del(struct keeper_modules* modules,struct keeper_module* module)
{
	return -1;
}

int keeper_modules_onenter(struct keeper_modules* modules,struct keeper_rec* rec)
{
	struct keeper_module *module;
	int                   ret_val;
	for(module = zend_llist_get_first(modules->mod_list);
		module != NULL;
		module = zend_llist_get_next(modules->mod_list))
	{
		ret_val = module->on_enter(rec);
		DO_MOD_FILTER(ret_val);
	}

	return SUCCESS;
}

int keeper_modules_oncall(struct keeper_modules* modules,struct keeper_rec* rec)
{
	struct keeper_module *module;
	int                   ret_val;
	for(module = zend_llist_get_first(modules->mod_list);
		module != NULL;
		module = zend_llist_get_next(modules->mod_list))
	{
		ret_val = module->on_call(rec);
		DO_MOD_FILTER(ret_val);
	}
	
	return SUCCESS;
}


int keeper_modules_onleave(struct keeper_modules* modules,struct keeper_rec* rec)
{
	struct keeper_module *module;
	int                   ret_val;
	for(module = zend_llist_get_first(modules->mod_list);
		module != NULL;
		module = zend_llist_get_next(modules->mod_list))
	{
		ret_val = module->on_leave(rec);
		DO_MOD_FILTER(ret_val);
	}
	
	return SUCCESS;
}
