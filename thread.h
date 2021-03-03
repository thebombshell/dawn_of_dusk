
/**
 * thread.h
 */

#ifndef DOD_THREAD_H
#define DOD_THREAD_H

typedef void* op_thread;

typedef void* op_atomic;

typedef void* op_mutex;

typedef void* op_semaphore;

typedef void (*thread_func)();

void thread_init(op_thread* t_thread, thread_func t_func);

void thread_final(op_thread* t_thread);

void thread_join(op_thread t_thread);

unsigned int thread_join_timeout(op_thread t_thread, unsigned long long int t_ms);

void atomic_init(op_atomic* t_atmoic, unsigned long long int t_value);

void atomic_final(op_atomic* t_atomic);

unsigned long long int atomic_increment(op_atomic t_atomic);

unsigned long long int atomic_decrement(op_atomic t_atomic);

void atomic_set(op_atomic t_atomic, unsigned long long int t_value);

unsigned long long int atomic_get(op_atomic t_atomic);

void mutex_init(op_mutex* t_mutex, unsigned int t_lock_now);

void mutex_final(op_mutex* t_mutex);

void mutex_wait(op_mutex t_mutex);

unsigned int mutex_wait_timeout(op_mutex t_mutex, unsigned long long int t_ms);

unsigned int mutex_try(op_mutex t_mutex);

void semaphore_init(op_semaphore* t_semaphore, unsigned long long int t_value, unsigned long long int t_limit);

void semaphore_final(op_semaphore* t_semaphore);

void semahpore_wait(op_semaphore t_semaphore);

unsigned int semahpore_wait_timeout(op_semaphore t_semaphore, unsigned long long int t_ms);

unsigned int semahpore_try(op_semaphore t_semaphore);

void semaphore_signal(op_semaphore t_semaphore, unsigned long long int t_value);

#endif