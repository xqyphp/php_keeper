#include "keeper_sapi.h"

static struct keeper_sapi g_keeper_sapi;

struct keeper_sapi* get_keeper_sapi()
{
	return &g_keeper_sapi;
}