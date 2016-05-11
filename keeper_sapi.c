#include "keeper_sapi.h"

static int my_register_handlers()
{
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