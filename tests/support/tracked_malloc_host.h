#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include "check.h"
void *__real_malloc(size_t size);
void *__real_calloc(size_t count, size_t size);
void __real_free(void *pointer);
static bool observe_allocation_heap;
static unsigned allocation_heap_calls, allocation_heap_reject, allocation_heap_failures, allocation_heap_frees;
static void *allocation_heap_allocations[4];
void *__wrap_malloc(size_t size)
{
    if(observe_allocation_heap && ++allocation_heap_calls == allocation_heap_reject) {
        allocation_heap_failures++;
        return NULL;
    }
    void *pointer = __real_malloc(size);
    if(observe_allocation_heap && pointer) {
        CHECK(allocation_heap_calls <= 4);
        allocation_heap_allocations[allocation_heap_calls - 1] = pointer;
    }
    return pointer;
}
void *__wrap_calloc(size_t count, size_t size)
{
    if(observe_allocation_heap && ++allocation_heap_calls == allocation_heap_reject) {
        allocation_heap_failures++;
        return NULL;
    }
    void *pointer = __real_calloc(count, size);
    if(observe_allocation_heap && pointer) {
        CHECK(allocation_heap_calls <= 4);
        allocation_heap_allocations[allocation_heap_calls - 1] = pointer;
    }
    return pointer;
}
void __wrap_free(void *pointer)
{
    for(unsigned i = 0; i < 4; i++) if(pointer && pointer == allocation_heap_allocations[i]) {
        allocation_heap_frees++;
        allocation_heap_allocations[i] = NULL;
        break;
    }
    __real_free(pointer);
}
