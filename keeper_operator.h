#ifndef keeper_filter_op_h
#define keeper_filter_op_h

struct keeper_operator
{
	/* data */
	int op_type;
	const char* op_name;
	int (*op_func)(struct keeper_rec* rec);
	void *op_data;
};

struct keeper_operators
{
	/* data */
	zend_llist             op_list;
	llist_dtor_func_t      op_dtor;
};
void keeper_operators_init();
void keeper_operators_destroy();

void keeper_operator_register_default();
void keeper_operator_register(struct keeper_operator* op);
struct keeper_filter_op*  keeper_operator_find(const char* name);

#endif