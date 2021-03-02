
/**
 * data.h
 */

#ifndef DOD_DATA_H
#define DOD_DATA_H

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	size_t size;
	void* data;

} buffer, *p_buffer;

/* initializes a buffer */
void buffer_init(buffer* t_buffer, size_t t_size);

/* resizes a buffer */
void buffer_resize(buffer* t_buffer, size_t t_size);

/* finalizes a buffer */
void buffer_final(buffer* t_buffer);

typedef struct
{
	buffer buffer;
	size_t element_size;
	unsigned int element_count;
} vector, *p_vector;

/* initialize a vector */
void vector_init(vector* t_vector, size_t t_element_size);

/* find the capcity of a vector */
unsigned int vector_find_capacity(vector* t_vector);

/* resizes a vector */
void vector_resize(vector* t_vector, unsigned int t_new_element_count);

/* resizes a vector, only if it needs to grow */
void vector_grow(vector* t_vector, unsigned int t_new_element_count);

/* finalize a vector */
void vector_final(vector* t_vector);

/* gets the pointer of an index in a vector */
void* vector_get_index(vector* t_vector, unsigned int t_index);

/* pushes an entry into a vector */
void vector_push(vector* t_vector, const void* t_data);

/* removes an entry at index from a vector */
void vector_remove(vector* t_vector, unsigned int t_index);

typedef struct
{
	void* data;
	void* prev;
	void* next;

} link, *p_link;

typedef struct
{
	link end;

} link_list, *p_link_list;

/* initialize a link list */
void link_list_init(link_list* t_list);

/* insert a link in a link list at a location */
p_link link_list_insert(p_link t_position, void* t_data);

/* move a link in a link list to a new location */
void link_list_move(p_link t_position, p_link t_link);

/* remove the provided link from its link list */
void link_list_remove(p_link t_link);

/* finalize a link list */
void link_list_final(link_list* t_list);

typedef struct
{
	const unsigned char hash;
	const char* const key;
	void* data;

} hash_pair, *p_hash_pair;

typedef struct
{
	link_list pairs;
	p_link buckets[256];

} hash_list, *p_hash_list;

/* hash functions */
unsigned char hash_string(const char* t_string);

/* allocates and initialize a hash pair */
p_hash_pair hash_pair_alloc(const char* t_key, void* t_data);

/* finalizes and frees a hash pair */
void hash_pair_free(p_hash_pair t_pair);

/* initialize hash list */
void hash_list_init(hash_list* t_list);

/* finalize hash list */
void hash_list_final(hash_list* t_list);

/* find an entry in a hash_list */
p_link hash_list_find(hash_list* t_list, const char* t_key);

/* insert an entry into a hash list */
p_link hash_list_insert(hash_list* t_list, const char* t_key, void* t_data);

/* remove an entry from a hash list */
void hash_list_remove(hash_list* t_list, p_link t_link);

#endif