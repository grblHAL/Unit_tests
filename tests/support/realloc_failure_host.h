#pragma once
#include <stdlib.h>
#include <stdbool.h>
static bool fail_realloc;
static unsigned failed_realloc_calls;
void *__real_realloc(void *pointer, size_t size);
void *__wrap_realloc(void *pointer, size_t size)
{
    if(fail_realloc) {
        failed_realloc_calls++;
        return NULL;
    }
    return __real_realloc(pointer, size);
}
