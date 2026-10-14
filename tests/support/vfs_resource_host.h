#pragma once
#include "support/vfs_operations_host.h"
#include <stddef.h>
void *__real_malloc(size_t size);
void *__real_calloc(size_t count, size_t size);
void *__real_realloc(void *ptr, size_t size);
static unsigned reject_malloc, reject_calloc, reject_realloc, malloc_failures, calloc_failures, realloc_failures;
static size_t rejected_size;
#ifdef TRACK_FAILED_REALLOC
void __real_free(void *ptr);
static void *failed_realloc_allocation;
static bool failed_realloc_released;
void __wrap_free(void *ptr)
{
    if(ptr && ptr == failed_realloc_allocation) failed_realloc_released = true;
    __real_free(ptr);
}
#endif
static unsigned malloc_matching_calls, reject_malloc_on_call;
void *__wrap_malloc(size_t size)
{
    if(size == rejected_size) {
        malloc_matching_calls++;
        if(reject_malloc || (reject_malloc_on_call && malloc_matching_calls == reject_malloc_on_call)) {
            if(reject_malloc) reject_malloc--;
            malloc_failures++; return NULL;
        }
    }
    return __real_malloc(size);
}
void *__wrap_calloc(size_t count, size_t size)
{
    if(reject_calloc) { reject_calloc--; calloc_failures++; return NULL; }
    return __real_calloc(count, size);
}

void *__wrap_realloc(void *ptr, size_t size)
{
    if(reject_realloc && size == rejected_size) {
#ifdef TRACK_FAILED_REALLOC
        failed_realloc_allocation = ptr;
#endif
        reject_realloc--; realloc_failures++; return NULL;
    }
    return __real_realloc(ptr, size);
}
