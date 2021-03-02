
/**
 * object_list.h
 */

#ifndef DOD_OBJECT_LIST_H
#define DOD_OBJECT_LIST_H

#include "data.h"
#include "object.h"
#include "typedef.h"

typedef struct {
	
	dod_uword x, y, z;
	
} object_chunk_header;

typedef struct {
	
	object_chunk_header header;
	list objects;
	
} object_chunk;

typedef struct {
	
	hash_list chunks;
	list live_objects;
	
} object_list;

#endif