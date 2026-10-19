#pragma once
#include "support/engine_host.h"
#include "check.h"
#include <string.h>
static inline status_code_t scaling_block(const char *text)
{
    char block[128]; CHECK(strlen(text) < sizeof(block));
    strcpy(block, text); return gc_execute_block(block);
}
