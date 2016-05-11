#include "keeper_header.h"
#include "keeper_rec.h"
#include "php_php_keeper.h"

static char* apm_get_server_info(const char *keyname TSRMLS_DC) {
#if(PHP_MAJOR_VERSION == 5 && (PHP_MINOR_VERSION < 4))
	zend_bool auto_globals_jit = (PG(auto_globals_jit) && !PG(register_globals) && !PG(register_long_arrays));
#else
	zend_bool auto_globals_jit = PG(auto_globals_jit);
#endif
	if (auto_globals_jit) {
		zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC);
	}

	zval **gServer = NULL;
	zval **gValue = NULL;
	if (zend_hash_find(&EG(symbol_table), ZEND_STRS("_SERVER"), (void**)&gServer) == SUCCESS) {
		if (zend_hash_find((*gServer)->value.ht, keyname, strlen(keyname) + 1, (void**)&gValue) == SUCCESS) {
			return estrdup(Z_STRVAL_PP(gValue));
		}
	}
	
	return NULL;
}

static char* php_get_header(const char* key)
{
	TSRMLS_FETCH();
	pj_str_t str_ret = pj_str("");
	char* value = apm_get_server_info(key TSRMLS_CC);
	if (value != NULL) {
		pj_strdup2_with_null(req->cycle->pool, &str_ret, value);
		efree(value);
	}
	return str_ret;
}


struct keeper_rec g_keeper_rec;

struct keeper_rec* get_keeper_rec()
{
	TSRMLS_FETCH();
	return &PHP_KEEPER_G(rec_data);
}

int keeper_rec_init()
{
	struct keeper_rec* krec = get_keeper_rec();

	return SUCCESS;
}

int keeper_rec_destroy()
{

	return SUCCESS;
}


int keeper_rec_oncall()
{

	return SUCCESS;
}