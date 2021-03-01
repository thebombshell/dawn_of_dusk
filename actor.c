
/**
 * actor.c
 */

#include "actor.h"
#include <assert.h>

void dod_object_extension_actor_init(dod_object_extension_actor* t_extension, dod_actor_tick_func t_tick) {
	
	assert(t_extension && t_tick);
	
	t_extension->header.type = DOD_OBJECT_EXTENSION_ACTOR;
	t_extension->header.next = 0;
	t_extension->header.final_func = dod_object_extension_actor_final;
	t_extension->tick = t_tick;
}

void dod_object_extension_actor_final(dod_object_extension_header* t_extension) {
	
	assert(t_extension);
	
	dod_object_extension_actor* actor = (dod_object_extension_actor*)t_extension;
	t_extension->tick = 0;
}