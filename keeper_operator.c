#include "keeper_operator.h"

static struct keeper_operators g_keeper_operators;

static void keeper_operators_dtor(void* data)
{

}

static struct keeper_operators* get_keeper_operators()
{
	return &g_keeper_operators;
}


void keeper_operators_init()
{
	 struct keeper_operators* pops = get_keeper_operators();
	 pops->op_dtor = keeper_operators_dtor;
	 zend_llist_init(pops->op_list,sizeof(struct keeper_operators),keeper_operators_dtor,1);
}

void keeper_operators_destroy()
{
	struct keeper_operators* pops = get_keeper_operators();
	zend_llist_clean(pops->op_list);
	return SUCCESS;
}

void keeper_operator_register_default()
{

}



void keeper_operator_register(struct keeper_operator* op)
{

}

struct keeper_filter_op*  keeper_operator_find(const char* name)
{

}