#ifndef keeper_module_h
#define keeper_module_h
#include "keeper_header.h"
#include "keeper_rec.h"

#define CHECK_MASK_ENTER 1
#define CHECK_MASK_CALL  1 << 1
#define CHECK_MASK_LEAVE 1 << 2

struct keeper_filter_op
{
	/* data */
	int type;
	int (*filter_op)();
};

struct keeper_module
{
	int (*on_enter)(void* data);
	int (*on_call)(void* data);
	int (*on_leave)(void* data);
	unsigned int check_mask;
	void *user_data;
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