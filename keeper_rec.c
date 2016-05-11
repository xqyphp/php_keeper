#include "keeper_rec.h"
#include "php.h"

struct keeper_rec g_keeper_rec;

struct keeper_rec* get_keeper_rec()
{
	return &g_keeper_rec;
}

int keeper_rec_init()
{
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