#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "strutils.h"
#include "check.h"
#include <stdlib.h>
#include <string.h>
void *__real_realloc(void *ptr, size_t size);
void __real_free(void *ptr);
static bool reject_growth;
static void *tracked_allocation;
static unsigned tracked_frees, rejected_growths;
void *__wrap_realloc(void *ptr, size_t size)
{
    if(reject_growth) { reject_growth = false; rejected_growths++; return NULL; }
    return __real_realloc(ptr, size);
}
void __wrap_free(void *ptr)
{
    if(ptr && ptr == tracked_allocation) tracked_frees++;
    __real_free(ptr);
}
