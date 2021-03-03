
/**
 * object.c
 */

#include "object.h"
#include <assert.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void dod_object_extension_header_init(dod_object_extension_header* t_header, dod_object_extension_type type, dod_object_extension_final_func t_final_func) {
	
	assert(t_header);
	
	t_header->type = type;
	t_header->next = 0;
	t_header->mutex = 0;
	mutex_init(&t_header->mutex, 1);
	t_header->final_func = t_final_func;
	
	mutex_release(t_header->mutex);
}

void dod_object_extension_header_final(dod_object_extension_header* t_header) {
	
	assert(t_header);
	
	t_header->type = 0;
	t_header->next = 0;
	mutex_wait(t_header->mutex);
	mutex_final(&t_header->mutex);
	t_header->final_func = 0;
	
}

void dod_object_init(dod_object* t_object, dod_uword t_chunk_x, dod_uword t_chunk_y, dod_uword t_chunk_z, dod_single t_x, dod_single t_y, dod_single t_z) {
	
	assert(t_object);
	
	t_object->id = 0;
	t_object->chunk_x = t_chunk_x;
	t_object->chunk_y = t_chunk_y;
	t_object->chunk_z = t_chunk_z;
	t_object->x = t_x;
	t_object->y = t_y;
	t_object->z = t_z;
	t_object->rotation = 0.0f;
	t_object->next = 0;
	t_object->info.value = 0xffffffffffffffff;
}

void dod_object_final(dod_object* t_object) {
	
	assert(t_object && !t_object->next);
	
	t_object->id = 0;
	t_object->chunk_x = 0;
	t_object->chunk_y = 0;
	t_object->chunk_z = 0;
	t_object->x = 0.0f;
	t_object->y = 0.0f;
	t_object->z = 0.0f;
	t_object->rotation = 0.0f;
	t_object->next = 0;
	t_object->info.value = 0xffffffffffffffff;
}

void dod_object_translate(dod_object* t_object, dod_single t_x, dod_single t_y, dod_single t_z) {
	
	assert(t_object);
	
	t_object->x += t_x;
	t_object->y += t_y;
	t_object->z += t_z;
	
	t_object->info.flags.x_dirty = 1;
	t_object->info.flags.y_dirty = 1;
	t_object->info.flags.z_dirty = 1;
	
	if (t_object->x < 0.0f || t_object->x >= 8.0f) {
		
		dod_single value = ((dod_single)t_object->chunk_x) * 8.0f + t_object->x;
		t_object->chunk_x = (dod_udword)floor(value / 8.0);
		t_object->x = value - ((dod_single)t_object->chunk_x) * 8.0f;
		t_object->info.flags.chunk_x_dirty = 1;
	}
	if (t_object->y < 0.0f || t_object->y >= 8.0f) {
		
		dod_single value = ((dod_single)t_object->chunk_y) * 8.0f + t_object->y;
		t_object->chunk_y = (dod_udword)floor(value / 8.0);
		t_object->y = value - ((dod_single)t_object->chunk_y) * 8.0f;
		t_object->info.flags.chunk_y_dirty = 1;
	}
	if (t_object->z < 0.0f || t_object->z >= 8.0f) {
		
		dod_single value = ((dod_single)t_object->chunk_z) * 8.0f + t_object->z;
		t_object->chunk_z = (dod_udword)floor(value / 8.0);
		t_object->z = value - ((dod_single)t_object->chunk_z) * 8.0f;
		t_object->info.flags.chunk_z_dirty = 1;
	}
}

void dod_object_teleport(dod_object* t_object, dod_uword t_chunk_x, dod_uword t_chunk_y, dod_uword t_chunk_z, dod_single t_x, dod_single t_y, dod_single t_z) {
	
	assert(t_object);
	
	t_object->chunk_x = t_chunk_x;
	t_object->chunk_y = t_chunk_y;
	t_object->chunk_z = t_chunk_z;
	t_object->x = t_x;
	t_object->y = t_y;
	t_object->z = t_z;
	t_object->info.flags.chunk_x_dirty = 1;
	t_object->info.flags.chunk_y_dirty = 1;
	t_object->info.flags.chunk_z_dirty = 1;
	t_object->info.flags.x_dirty = 1;
	t_object->info.flags.y_dirty = 1;
	t_object->info.flags.z_dirty = 1;
}

void dod_object_rotate(dod_object* t_object, dod_single t_delta) {
	
	assert(t_object);
	
	t_object->rotation = (dod_single)fmod(t_object->rotation + t_delta, M_PI * 2.0);
	t_object->info.flags.rotation_dirty = 1;
}

void dod_object_set_rotation(dod_object* t_object, dod_single t_rotation) {
	
	assert(t_object);
	
	t_object->rotation = (dod_single)fmod(t_rotation, M_PI * 2.0);
	t_object->info.flags.rotation_dirty = 1;
}

void dod_object_extend(dod_object* t_object, dod_object_extension_header* t_next) {
	
	assert(t_object);
	assert(!t_next->next && "an extension must be non-extended (next == 0), the object may be multiple extended instead");
	
	if (t_object->next) {
		
		t_next->next = t_object->next;
	}
	t_object->next = t_next;
	t_object->info.flags.next_dirty = 1;
}

dod_uword dod_object_get_extension(dod_object* t_object) {
	
	assert(t_object);
	
	return t_object->next ? (t_object->next->type) : 0;
}

void dod_object_foreach_extension(dod_object* t_object, dod_object_foreach_extension_func t_func) {
	
	assert(t_object && t_func);
	
	dod_object_extension_header* extension = t_object->next;
	while (extension) {
		
		dod_object_extension_header* next = extension->next;
		t_func(extension);
		extension = next;
	}
}

void dod_object_final_extensions(dod_object* t_object) {
	
	assert(t_object);
	
	dod_object_extension_header* extension = t_object->next;
	while (extension) {
		
		dod_object_extension_header* next = extension->next;
		extension->final_func(extension);
		extension = next;
	}
}
