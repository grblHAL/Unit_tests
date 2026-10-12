#pragma once
#include <stdlib.h>
#include <stdbool.h>
static bool fail_malloc;
static unsigned failed_malloc_calls;
void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size)
{
    if(fail_malloc) {
        failed_malloc_calls++;
        return NULL;
    }
    return __real_malloc(size);
}
