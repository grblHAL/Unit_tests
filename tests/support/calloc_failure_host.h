#pragma once
#include <stdlib.h>
#include <stdbool.h>
static bool fail_calloc;
static unsigned failed_calloc_calls;
void *__real_calloc(size_t count, size_t size);
void *__wrap_calloc(size_t count, size_t size)
{
    if(fail_calloc) {
        failed_calloc_calls++;
        return NULL;
    }
    return __real_calloc(count, size);
}
