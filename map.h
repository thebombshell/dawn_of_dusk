
/**
 * map.h
 */

#ifndef DOD_MAP_H
#define DOD_MAP_H

#include "typedef.h"
#include "data.h"
#include "piece.h"

#define DOD_MAP_CHUNK_WIDTH 8
#define DOD_MAP_CHUNK_HEIGHT 8
#define DOD_MAP_CHUNK_DEPTH 8
#define DOD_MAP_CHUNK_SIZE (DOD_MAP_CHUNK_WIDTH * DOD_MAP_CHUNK_HEIGHT * DOD_MAP_CHUNK_DEPTH)

typedef struct {
	
	dod_uword value;
	struct {
		
		dod_bool is_looping_width : 1;
		dod_bool is_looping_height : 2;
		
	} flags;
	
} dod_map_info;

typedef struct {
	
	dod_udword type;
	dod_udword params[1024];
	
} dod_map_gen_info;

typedef struct {
	
	dod_udword x, y, z;
	
} dod_map_chunk_header;

typedef struct {
	
	dod_map_chunk_header header;
	dod_piece pieces[DOD_MAP_CHUNK_SIZE];
	
} dod_map_chunk;

typedef struct {
	
	dod_map_info info;
	dod_map_gen_info dod_map_gen_info;
	dod_udword width;
	dod_udword height;
	dod_udword depth;
	
} dod_map_header;

typedef struct {
	
	dod_map_header header;
	hash_list chunk_list;
	
} dod_map;

void dod_map_init(dod_map* t_map, dod_map_info t_value, dod_udword t_w, dod_udword t_h, dod_udword t_d);

void dod_map_final(dod_map* t_map);

dod_map_chunk* dod_map_chunk_init(dod_map* t_map, dod_udword t_x, dod_udword t_y, dod_udword t_z);

void dod_map_chunk_final(dod_map* t_map, dod_udword t_x, dod_udword t_y, dod_udword t_z);

dod_map_chunk* dod_map_get_chunk(dod_map* t_map, dod_udword t_x, dod_udword t_y, dod_udword t_z);

#endif