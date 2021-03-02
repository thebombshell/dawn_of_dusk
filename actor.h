
/**
 * actor.h
 */

#ifndef DOD_ACTOR_H
#define DOD_ACTOR_H

#include "object.h"

typedef void (*dod_actor_tick_func)(dod_object* t_object);

typedef struct {
	
	dod_object_extension_header header;
	dod_actor_tick_func tick;
	
} dod_object_extension_actor;

void dod_object_extension_actor_init(dod_object_extension_actor* t_extension, dod_actor_tick_func tick);

void dod_object_extension_actor_final(void* t_extension);

#endif