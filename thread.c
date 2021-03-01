
#include "thread.h"

#include <assert.h>

#ifdef WIN32

#include "c89atomic.h"
#include <windows.h>

typedef struct {
	
	HANDLE thread;
	thread_func func;
	
} thread_impl;

DWORD WINAPI thread_proc(_In_ LPVOID t_param) {
	
	thread_impl* thread = (thread_impl*)t_param;
	thread->func();
}

void thread_init(op_thread* t_thread, thread_func t_func) {
	
	assert(t_thread && t_func);
	
	thread_impl* output = (thread_impl*)malloc(sizeof(thread_impl));
	output->func = t_func;
	output->thread = CreateThread(0, 0, thread_proc, output, 0, 0);
	assert(output->thread);
	*t_thread = (op_thread)output;
}

void thread_final(op_thread* t_thread) {
	
	assert(t_thread);
	
	thread_impl* thread = (thread_impl*)(*t_thread);
	CloseHandle((thread)->thread);
	free(*t_thread);
	*t_thread = 0;
}

void thread_join(op_thread t_thread) {
	
	assert(t_thread);
	
	thread_impl* thread = (thread_impl*)t_thread;
	WaitForSingleObject(thread->thread, INFINITE);
}

unsigned int thread_join_timeout(op_thread t_thread, unsigned long long int t_ms) {
	
	assert(t_thread);
	
	DWORD result = WaitForSingleObject(t_thread->thread, (DWORD)t_ms);
	return result == 0 ? 1 : 0;
}

typedef struct {
	
	c89atomic_uint64 value;
	
} atomic_impl;

void atomic_init(op_atomic* t_atmoic, unsigned long long int t_value) {
	
	assert(t_atomic);
	
	atomic_impl* output = (atomic_impl*)malloc(sizeof(atomic_impl));
	c89atomic_store_64(&output->value, t_value);
	
	*t_atmoic = (op_atomic)output;
}

void atomic_final(op_atomic* t_atomic) {
	
	assert(t_atomic);
	
	free(t_atomic);
	*t_atomic = 0;
}

unsigned long long int atomic_increment(op_atomic t_atomic) {
	
	assert(t_atomic);
	
	atomic_impl* atomic = (atomic_impl*)t_atmoic;
	return (unsigned long long int)c89atomic_fetch_add_64(&atomic->value, 1);
}

unsigned long long int atomic_decrement(op_atomic t_atomic) {
	
	assert(t_atomic);
	
	atomic_impl* atomic = (atomic_impl*)t_atmoic;
	return (unsigned long long int)c89atomic_fetch_sub_64(&atomic->value, 1);
}

void atomic_set(op_atomic t_atomic, unsigned long long int t_value) {
	
	assert(t_atomic);
	
	atomic_impl* atomic = (atomic_impl*)t_atmoic;
	c89atomic_store_64(&atomic->value, t_value);
}

unsigned long long int atomic_get(op_atomic t_atomic) {
	
	assert(t_atomic);
	
	atomic_impl* atomic = (atomic_impl*)t_atmoic;
	return (unsigned long long int)c89atomic_load_64(&atomic->value);
}

typedef struct {
	
	HANDLE mutex;
	
} mutex_impl;

void mutex_init(op_mutex* t_mutex, unsigned int t_lock_now) {
	
	assert(t_mutex);
	
	mutex_impl* output = (mutex_impl*)malloc(sizeof(mutex_impl));
	output->mutex = CreateMutex(0, t_lock_now, 0);
	*t_mutex = (op_mutex)output;
}

void mutex_final(op_mutex* t_mutex) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)*t_mutex;
	CloseHandle(mutex->mutex);
	free(mutex);
	*t_mutex = 0;
}

void mutex_wait(op_mutex t_mutex) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)t_mutex;
	WaitForSingleObject(mutex->mutex, INFINITE);
}

unsigned int mutex_wait_timeout(op_mutex t_mutex, unsigned long long int t_ms) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)t_mutex;
	DWORD result = WaitForSingleObject(mutex->mutex, (DWORD)t_ms);
	return result == 0 ? 1 : 0;
}

unsigned int mutex_try(op_mutex t_mutex) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)t_mutex;
	DWORD result = WaitForSingleObject(mutex->mutex, 0);
	return result == 0 ? 1 : 0;
}

void semaphore_init(op_semaphore* t_semaphore, unsigned long long int t_value, unsigned long long int t_limit);

void semaphore_final(op_semaphore* t_semaphore);

void semahpore_wait(op_semaphore t_semaphore);

unsigned int semahpore_wait_timeout(op_semaphore t_semaphore, unsigned long long int t_ms);

unsigned int semahpore_try(op_semaphore t_semaphore);

void semaphore_signal(op_semaphore t_semaphore, unsigned long long int t_value);

#endif