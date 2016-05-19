#include "keeper_header.h"
#include "keeper_rec.h"
#include "php_php_keeper.h"

ZEND_EXTERN_MODULE_GLOBALS(php_keeper)

struct keeper_rec_globals *get_keeper_rec_globals();

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

static const char* php_get_request_uri()
{
	TSRMLS_FETCH();
	return SG(request_info).request_uri;
}

static const char* php_get_request_method()
{
	TSRMLS_FETCH();
	return SG(request_info).request_method;
}

static HashTable*  php_get_request_headers()
{
	TSRMLS_FETCH();
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
		return (*gServer)->value.ht;
	}
	
	return NULL;
}

static HashTable*  php_get_request_params()
{
	TSRMLS_FETCH();
	zval *symbol_table = PG(http_globals)[TRACK_VARS_REQUEST];
	return Z_ARRVAL_P(symbol_table);
}

static HashTable*  php_get_request_cookies()
{
	TSRMLS_FETCH();
	zval *symbol_table = PG(http_globals)[TRACK_VARS_COOKIE];
	return Z_ARRVAL_P(symbol_table);
}

static const char* php_get_hash_value_str(HashTable* ht,const char* name)
{
	zval **rval = NULL;
	if (zend_hash_find(ht, ZEND_STRS(name), (void**)&rval) == SUCCESS) {
		return Z_STRVAL_PP(rval);
	}
}

static const char* php_get_request_header(const char* name)
{
	HashTable* ht = php_get_request_headers();
	return php_get_hash_value_str(ht,name);
}

static const char* php_get_request_param(const char* name)
{
	HashTable* ht = php_get_request_params();
	return php_get_hash_value_str(ht,name);
}

static const char* php_get_request_cookie(const char* name)
{
	HashTable* ht = php_get_request_cookies();
	return php_get_hash_value_str(ht,name);
}

static const char* php_get_class_name()
{
	struct keeper_rec_globals* rg = get_keeper_rec_globals();
	return rg->rg_cls;
}

static const char* php_get_function_name()
{
	struct keeper_rec_globals* rg = get_keeper_rec_globals();
	return rg->rg_func;
}

static int php_get_fargc()
{
	struct keeper_rec_globals* rg = get_keeper_rec_globals();
	return rg->rg_argc;
}

static zval* php_get_farg(int index)
{
	struct keeper_rec_globals* rg = get_keeper_rec_globals();
	if(index < 0 || index >= rg->rg_argc){
		return NULL;
	}
	return rg->rg_argv[index];
}

static struct keeper_rec g_keeper_rec={
	php_get_request_uri,
	php_get_request_method,
	php_get_request_headers,
	php_get_request_params,
	php_get_request_cookies,
	php_get_request_header,
	php_get_request_param,
	php_get_request_cookie,
	php_get_class_name,
	php_get_function_name,
	php_get_fargc,
	php_get_farg
};

struct keeper_rec* get_keeper_rec()
{
	return &g_keeper_rec;
}

struct keeper_rec_globals *get_keeper_rec_globals()
{
	TSRMLS_FETCH();
	return &PHP_KEEPER_G(rec_data);
}

int keeper_rec_init()
{
	TSRMLS_FETCH();
	struct keeper_rec* krec = get_keeper_rec();
	struct keeper_rec_globals *globals = get_keeper_rec_globals();
	globals->status = 0;
	globals->rg_cls = NULL;
	globals->rg_func = NULL;
	globals->rg_argc = 0;
	globals->rg_argv = NULL;
	return SUCCESS;
}

int keeper_rec_oncall()
{
	TSRMLS_FETCH();
	struct keeper_rec* krec = get_keeper_rec();
	struct keeper_rec_globals *globals = get_keeper_rec_globals();
	globals->status = 1;
	return SUCCESS;
}

int keeper_rec_destroy()
{
	TSRMLS_FETCH();
	struct keeper_rec* krec = get_keeper_rec();
	struct keeper_rec_globals *globals = get_keeper_rec_globals();
	globals->status = 2;
	globals->rg_cls = NULL;
	globals->rg_func = NULL;
	globals->rg_argc = 0;
	globals->rg_argv = NULL;
	return SUCCESS;
}

