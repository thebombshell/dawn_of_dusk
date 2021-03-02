
#include "map.h"

#include <assert.h>
#include <stdio.h>

void position_to_characters(dod_udword t_x, dod_udword t_y, dod_udword t_z, dod_string t_output)
{
	assert(t_output);
	
	sprintf(t_output, "%20llu,%20llu,%20llu", t_x, t_y, t_z);
}

void dod_map_init(dod_map* t_map, dod_map_info t_value, dod_udword t_w, dod_udword t_h, dod_udword t_d)
{
	assert(t_map && t_w && t_h && t_d);
	
	t_map->header.info = t_value;
	t_map->header.width = t_w;
	t_map->header.height = t_h;
	t_map->header.depth = t_d;
}

void dod_map_final(dod_map* t_map)
{
	assert(t_map);
}

dod_map_chunk* dod_map_chunk_init(dod_map* t_map, dod_udword t_x, dod_udword t_y, dod_udword t_z)
{
	assert(t_map);
	
	dod_char string[64];
	position_to_characters(t_x, t_y, t_z, string);
	
	dod_map_chunk* chunk = calloc(1, sizeof(dod_map_chunk));
	chunk->header.x = t_x;
	chunk->header.y = t_y;
	chunk->header.z = t_z;
	
	hash_list_insert(&t_map->chunk_list, string, chunk);
	return chunk;
}

void dod_map_chunk_final(dod_map* t_map, dod_udword t_x, dod_udword t_y, dod_udword t_z)
{
	assert(t_map);
	
	dod_char string[64];
	position_to_characters(t_x, t_y, t_z, string);
	p_link link = hash_list_find(&t_map->chunk_list, string);
	if (link)
	{
		p_hash_pair pair = (p_hash_pair)link->data;
		free(pair->data);
		hash_list_remove(&t_map->chunk_list, link);
	}
}

dod_map_chunk* dod_map_get_chunk(dod_map* t_map, dod_udword t_x, dod_udword t_y, dod_udword t_z)
{
	assert(t_map);
	
	dod_char string[64];
	position_to_characters(t_x, t_y, t_z, string);
	
	p_link link = hash_list_find(&t_map->chunk_list, string);
	if (!link)
	{
		return 0;
	}
	
	p_hash_pair pair = (p_hash_pair)link->data;
	return pair->data;
}