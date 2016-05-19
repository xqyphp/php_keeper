#include "keeper_sapi.h"
#include "keeper_header.h"

ZEND_EXTERN_MODULE_GLOBALS(php_keeper);


static int php_taint_include_or_eval_handler(ZEND_OPCODE_HANDLER_ARGS) /* {{{ */ {
	return ZEND_USER_OPCODE_DISPATCH;
} /* }}} */

static int php_taint_fcall_check(const char* cname,const char* fname,zval** argv,int argc) /* {{{ */ {
	
} /* }}} */

static int php_taint_fcall_check2(ZEND_OPCODE_HANDLER_ARGS, zend_op *opline, zend_class_entry *scope, char *fname){
	
	const char* cname = "";
	void **p = NULL;
	int argc = 0;

	if(scope){
		const char* cname = scope->name;
	}

	if(fname){
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION > 3)
		p = EG(argument_stack)->top;
#elif (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION > 2)
		p = EG(argument_stack)->top;
#else
		p = EG(argument_stack).top_element;
#endif
		argc = opline->extended_value;
	}

	return php_taint_fcall_check(cname, fname, (zval**)p, argc);
}

static int php_taint_fcall_handler(ZEND_OPCODE_HANDLER_ARGS) /* {{{ */ {
	int rt = ZEND_USER_OPCODE_DISPATCH;
	zend_op *opline = execute_data->opline;
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION >= 5)
	zend_class_entry *scope = execute_data->call->fbc->common.scope;
	char *fname = (char *)(execute_data->call->fbc->common.function_name);
#else
	zend_class_entry *scope = execute_data->fbc->common.scope;
	char *fname = (char *)(execute_data->fbc->common.function_name);
#endif

#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 3)
	zend_function *old_func = EG(function_state_ptr)->function;
	EG(function_state_ptr)->function = execute_data->fbc;
	rt = php_taint_fcall_check2(ZEND_OPCODE_HANDLER_ARGS_PASSTHRU, opline, scope, fname);
	EG(function_state_ptr)->function = old_func;
#else
	zend_function *old_func = EG(current_execute_data)->function_state.function;
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION >= 5)
	EG(current_execute_data)->function_state.function = execute_data->call->fbc;
#else
	EG(current_execute_data)->function_state.function = execute_data->fbc;
#endif
	rt = php_taint_fcall_check2(ZEND_OPCODE_HANDLER_ARGS_PASSTHRU, opline, scope, fname);
	EG(current_execute_data)->function_state.function = old_func;
#endif

	return rt;
} /* }}} */


static int my_register_handlers()
{
	//zend_set_user_opcode_handler(ZEND_ECHO, php_taint_echo_handler);
	//zend_set_user_opcode_handler(ZEND_EXIT, php_taint_exit_handler);
	//zend_set_user_opcode_handler(ZEND_INIT_USER_CALL, php_taint_init_dynamic_fcall_handler);
	//zend_set_user_opcode_handler(ZEND_INIT_DYNAMIC_CALL, php_taint_init_dynamic_fcall_handler);
	zend_set_user_opcode_handler(ZEND_INCLUDE_OR_EVAL, php_taint_include_or_eval_handler);
	//zend_set_user_opcode_handler(ZEND_CONCAT, php_taint_concat_handler);
	//zend_set_user_opcode_handler(ZEND_FAST_CONCAT, php_taint_concat_handler);
	//zend_set_user_opcode_handler(ZEND_ASSIGN_CONCAT, php_taint_assign_concat_handler);
	//zend_set_user_opcode_handler(ZEND_ROPE_END, php_taint_rope_handler);
	zend_set_user_opcode_handler(ZEND_DO_FCALL, php_taint_fcall_handler);
	//zend_set_user_opcode_handler(ZEND_DO_ICALL, php_taint_fcall_handler);
	zend_set_user_opcode_handler(ZEND_DO_FCALL_BY_NAME, php_taint_fcall_handler);
	return SUCCESS;
}

static int my_unregister_handlers()
{
	return SUCCESS;
}

static int my_register_overrides()
{
	return SUCCESS;
}

static int my_unregister_overrides()
{
	return SUCCESS;
}

static struct keeper_setting* my_load_setting()
{
	return NULL;
}

static int my_reload_setting()
{
	return SUCCESS;
}

static int my_http_forbidden()
{
	TSRMLS_FETCH();
	sapi_header_line ctr = { 0 };

	ctr.line = "HTTP/1.0 403 Forbidden";
	ctr.line_len = sizeof("HTTP/1.0 403 Forbidden") - 1;
	sapi_header_op(SAPI_HEADER_REPLACE, &ctr TSRMLS_CC);

	/* restore memory limit */
	zend_set_memory_limit(PG(memory_limit));
	zend_objects_store_mark_destructed(&EG(objects_store) TSRMLS_CC);

	zend_bailout();
}

static struct keeper_sapi g_keeper_sapi=
{
	my_register_handlers,
	my_unregister_handlers,
	my_register_overrides,
	my_unregister_overrides,
	my_load_setting,
	my_reload_setting,
	my_http_forbidden
};

struct keeper_sapi* get_keeper_sapi()
{
	return &g_keeper_sapi;
}