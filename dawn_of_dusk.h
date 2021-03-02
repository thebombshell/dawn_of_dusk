
/**
 * dawn_of_dusk.h
 */

#ifndef DOD_DAWN_OF_DUSK_H
#define DOD_DAWN_OF_DUSK_H

#include "map.h"

typedef struct {
	
	dod_map map;
	
} dod_world;

void dod_world_init(dod_world* t_world);

void dod_world_final(dod_world* t_world);

void dod_world_command(dod_world* t_world, dod_string t_command);

void dod_world_run(dod_world* t_world);

void dod_world_stop(dod_world* t_world);

dod_bool dod_world_is_running(dod_world* t_world);

#endif