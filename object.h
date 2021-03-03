
/**
 * object.h
 */

#ifndef DOD_OBJECT_H
#define DOD_OBJECT_H

#include "typedef.h"
#include "thread.h"

typedef dod_uword dod_object_extension_type;

#define DOD_OBJECT_EXTENSION_INVALID (0x00000000)
#define DOD_OBJECT_EXTENSION_ACTOR (0x00000001)
#define DOD_OBJECT_EXTENSION_RIGIDBODY (0x00000002)

typedef union {
	
	dod_udword value;
	struct {
		
		dod_bool id_dirty : 1;
		dod_bool chunk_x_dirty : 1;
		dod_bool chunk_y_dirty : 1;
		dod_bool chunk_z_dirty : 1;
		dod_bool x_dirty : 1;
		dod_bool y_dirty : 1;
		dod_bool z_dirty : 1;
		dod_bool rotation_dirty : 1;
		dod_bool next_dirty : 1;
	} flags;
	
} dod_object_info;

typedef void (*dod_object_extension_final_func)(void* t_extension);

typedef struct dod_object_extension_header {
	
	dod_object_extension_type type;
	struct dod_object_extension_header* next;
	op_mutex mutex;
	dod_object_extension_final_func final_func;
	
} dod_object_extension_header;

typedef struct {
	
	dod_udword id;
	dod_uword chunk_x, chunk_y, chunk_z;
	dod_single x, y, z;
	dod_single rotation;
	dod_object_info info;
	op_mutex mutex;
	dod_object_extension_header* next;
	
} dod_object;

void dod_object_extension_header_init(dod_object_extension_header* t_header, dod_object_extension_type type, dod_object_extension_final_func t_final_func);

void dod_object_extension_header_final(dod_object_extension_header* t_header);

void dod_object_init(dod_object* t_object, dod_uword t_chunk_x, dod_uword t_chunk_y, dod_uword t_chunk_z, dod_single t_x, dod_single t_y, dod_single t_z);

void dod_object_final(dod_object* t_object);

void dod_object_translate(dod_object* t_object, dod_single t_x, dod_single t_y, dod_single t_z);

void dod_object_teleport(dod_object* t_object, dod_uword t_chunk_x, dod_uword t_chunk_y, dod_uword t_chunk_z, dod_single t_x, dod_single t_y, dod_single t_z);

void dod_object_rotate(dod_object* t_object, dod_single t_delta);

void dod_object_set_rotation(dod_object* t_object, dod_single t_rotation);

void dod_object_extend(dod_object* t_object, dod_object_extension_header* t_next);

dod_uword dod_object_get_extension(dod_object* t_object);

typedef void(*dod_object_foreach_extension_func)(dod_object_extension_header* t_extension);

void dod_object_foreach_extension(dod_object* t_object, dod_object_foreach_extension_func t_func);

void dod_object_final_extensions(dod_object* t_object);

#endif