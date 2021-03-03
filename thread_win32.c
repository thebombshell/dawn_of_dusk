
/**
 * thread_win32.c
 */

#ifdef _WIN32

#include "thread.h"

#include <assert.h>
#include <windows.h>

typedef struct {
	
	HANDLE thread;
	thread_func func;
	void* argument;
	
} thread_impl;

DWORD WINAPI thread_proc(LPVOID t_param) {
	
	thread_impl* thread = (thread_impl*)t_param;
	thread->func(thread->argument);
	
	return 0;
}

void thread_init(op_thread* t_thread, thread_func t_func, void* t_arg) {
	
	assert(t_thread && t_func);
	
	thread_impl* output = (thread_impl*)malloc(sizeof(thread_impl));
	output->func = t_func;
	output->argument = t_arg;
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
	
	thread_impl* thread = (thread_impl*)t_thread;
	DWORD result = WaitForSingleObject(thread->thread, (DWORD)t_ms);
	return result == 0 ? 1 : 0;
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

void mutex_release(op_mutex t_mutex) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)t_mutex;
	ReleaseMutex(mutex->mutex);
}

typedef struct {
	
	HANDLE semaphore;
	
} semaphore_impl;

void semaphore_init(op_semaphore* t_semaphore, unsigned long long int t_value, unsigned long long int t_limit) {
	
	assert(t_semaphore && t_limit);
	
	semaphore_impl* semaphore = (semaphore_impl*)malloc(sizeof(semaphore_impl));
	semaphore->semaphore = CreateSemaphore(0, (LONG)t_value, (LONG)t_limit, 0);
	assert(semaphore->semaphore);
	*t_semaphore = (op_semaphore)semaphore;
}

void semaphore_final(op_semaphore* t_semaphore) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	CloseHandle(semaphore->semaphore);
	free(*t_semaphore);
	*t_semaphore = 0;
}

void semahpore_wait(op_semaphore t_semaphore) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	WaitForSingleObject(semaphore->semaphore, INFINITE);
}


unsigned int semahpore_wait_timeout(op_semaphore t_semaphore, unsigned long long int t_ms) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	DWORD result = WaitForSingleObject(semaphore->semaphore, (DWORD)t_ms);
	return result == 0 ? 1 : 0;
}

unsigned int semahpore_try(op_semaphore t_semaphore) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	DWORD result = WaitForSingleObject(semaphore->semaphore, 0);
	return result == 0 ? 1 : 0;
}

void semaphore_signal(op_semaphore t_semaphore, unsigned long long int t_value) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	ReleaseSemaphore(semaphore->semaphore, t_value, 0);
}

#endif