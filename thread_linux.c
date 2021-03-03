
/**
 * thread_linux.c
 */

#ifdef __linux__

#include "thread.h"

#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

typedef struct {
	
	pthread_t thread;
	thread_func func;
	void* argument;
	
} thread_impl;

void* thread_proc(void* t_param) {
	
	assert(t_param);
	
	thread_impl* thread = (thread_impl*)t_param;
	thread->func(thread->argument);
	
	return 0;
}

void thread_init(op_thread* t_thread, thread_func t_func, void* t_arg) {
	
	assert(t_thread && t_func);
	
	thread_impl* output = (thread_impl*)malloc(sizeof(thread_impl));
	output->func = t_func;
	output->argument = t_arg;
	pthread_create(&output->thread, 0, thread_proc, output); 
	*t_thread = (op_thread)output;
}

void thread_final(op_thread* t_thread) {
	
	assert(t_thread);
	
	thread_impl* thread = (thread_impl*)(*t_thread);
	free(thread);
	*t_thread = 0;
}

void thread_join(op_thread t_thread) {
	
	assert(t_thread);
	
	thread_impl* thread = (thread_impl*)t_thread;
	pthread_join(thread->thread, 0);
}

unsigned int thread_join_timeout(op_thread t_thread, unsigned long long int t_ms) {
	
	assert(t_thread);
	
	thread_impl* thread = (thread_impl*)t_thread;
	
	if (t_ms) {
	
		long int ms = (long int)(t_ms % 1000); 
		struct timespec timeout = { .tv_sec=(time_t)((t_ms - ms) / 1000), .tv_nsec=ms * 1000000 };
		pthread_timedjoin_np(thread->thread, 0, &timeout);
	}
	else {
		
		pthread_tryjoin_np(thread->thread, 0);
	}
}

typedef struct {
	
	pthread_mutex_t mutex;
	
} mutex_impl;

void mutex_init(op_mutex* t_mutex, unsigned int t_lock_now) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)malloc(sizeof(mutex_impl));
	pthread_mutex_init(&mutex->mutex, 0);
	if (t_lock_now) {
		
		pthread_mutex_lock(&mutex->mutex);
	}
	*t_mutex = (op_mutex)mutex;
}

void mutex_final(op_mutex* t_mutex) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)(*t_mutex);
	pthread_mutex_destroy(&mutex->mutex);
	free(mutex);
	*t_mutex = 0;
}

void mutex_wait(op_mutex t_mutex) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)t_mutex;
	pthread_mutex_lock(&mutex->mutex);
}

unsigned int mutex_wait_timeout(op_mutex t_mutex, unsigned long long int t_ms) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)t_mutex;
	long int ms = (long int)(t_ms % 1000); 
	struct timespec timeout = { .tv_sec=(time_t)((t_ms - ms) / 1000), .tv_nsec=ms * 1000000 };
	return pthread_mutex_timedlock(&mutex->mutex, &timeout) ? 0 : 1;
}

unsigned int mutex_try(op_mutex t_mutex) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)t_mutex;
	return pthread_mutex_trylock(&mutex->mutex) ? 0 : 1;
}

void mutex_release(op_mutex t_mutex) {
	
	assert(t_mutex);
	
	mutex_impl* mutex = (mutex_impl*)t_mutex;
	pthread_mutex_unlock(&mutex->mutex);
}

typedef struct {
	
	sem_t semaphore;
	
} semaphore_impl;

void semaphore_init(op_semaphore* t_semaphore, unsigned long long int t_value, unsigned long long int t_limit) {
	
	assert(t_semaphore);
	assert(t_limit > 1 && "limit not supported by linux");
	
	semaphore_impl* output = (semaphore_impl*)malloc(sizeof(semaphore_impl));
	if (sem_init(&output->semaphore, 0, t_value) != 0)
	{
		assert(0 && "sem_init failed");
	}
	*t_semaphore = output;
}

void semaphore_final(op_semaphore* t_semaphore) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	sem_destroy(&semaphore->semaphore);
	free(semaphore);
	*t_semaphore = 0;
}

void semahpore_wait(op_semaphore t_semaphore) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	sem_wait(&semaphore->semaphore);
}

unsigned int semahpore_wait_timeout(op_semaphore t_semaphore, unsigned long long int t_ms) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	long int ms = (long int)(t_ms % 1000); 
	struct timespec timeout = { .tv_sec=(time_t)((t_ms - ms) / 1000), .tv_nsec=ms * 1000000 };
	return sem_timedwait(&semaphore->semaphore, &timeout) ? 0 : 1;
}

unsigned int semahpore_try(op_semaphore t_semaphore) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	return sem_trywait(&semaphore->semaphore) ? 0 : 1;
}

void semaphore_signal(op_semaphore t_semaphore, unsigned long long int t_value) {
	
	assert(t_semaphore);
	
	semaphore_impl* semaphore = (semaphore_impl*)t_semaphore;
	while (t_value) {
		
		--t_value;
		sem_post(&semaphore->semaphore);
	}
}

#endif