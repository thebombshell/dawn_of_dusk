
/**
 * actor.c
 */

#include "actor.h"
#include <assert.h>

void dod_object_extension_actor_init(dod_object_extension_actor* t_extension, dod_actor_tick_func t_tick) {
	
	assert(t_extension && t_tick);
	
	dod_object_extension_header_init(&t_extension->header, DOD_OBJECT_EXTENSION_ACTOR, dod_object_extension_actor_final);
	t_extension->tick = t_tick;
}

void dod_object_extension_actor_final(void* t_extension) {
	
	assert(t_extension);
	
	dod_object_extension_actor* actor = (dod_object_extension_actor*)t_extension;
	
	assert(actor->header.type == DOD_OBJECT_EXTENSION_ACTOR);
	
	dod_object_extension_header_final(&actor->header);
	actor->tick = 0;
}