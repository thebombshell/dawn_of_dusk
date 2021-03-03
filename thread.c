
/**
 * thread.c
 */

#include "thread.h"

#include <assert.h>
#include "c89atomic.h"
#include <stdlib.h>

typedef struct {
	
	c89atomic_uint64 value;
	
} atomic_impl;

void atomic_init(op_atomic* t_atomic, unsigned long long int t_value) {
	
	assert(t_atomic);
	
	atomic_impl* output = (atomic_impl*)malloc(sizeof(atomic_impl));
	c89atomic_store_64(&output->value, t_value);
	
	*t_atomic = (op_atomic)output;
}

void atomic_final(op_atomic* t_atomic) {
	
	assert(t_atomic);
	
	free(t_atomic);
	*t_atomic = 0;
}

unsigned long long int atomic_increment(op_atomic t_atomic) {
	
	assert(t_atomic);
	
	atomic_impl* atomic = (atomic_impl*)t_atomic;
	return (unsigned long long int)c89atomic_fetch_add_64(&atomic->value, 1);
}

unsigned long long int atomic_decrement(op_atomic t_atomic) {
	
	assert(t_atomic);
	
	atomic_impl* atomic = (atomic_impl*)t_atomic;
	return (unsigned long long int)c89atomic_fetch_sub_64(&atomic->value, 1);
}

void atomic_set(op_atomic t_atomic, unsigned long long int t_value) {
	
	assert(t_atomic);
	
	atomic_impl* atomic = (atomic_impl*)t_atomic;
	c89atomic_store_64(&atomic->value, t_value);
}

unsigned long long int atomic_get(op_atomic t_atomic) {
	
	assert(t_atomic);
	
	atomic_impl* atomic = (atomic_impl*)t_atomic;
	return (unsigned long long int)c89atomic_load_64(&atomic->value);
}