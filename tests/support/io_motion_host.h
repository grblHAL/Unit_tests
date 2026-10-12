#pragma once
#include "support/motion_program_host.h"
#include "support/ioports_host.h"
static inline void prepare_io_motion(void)
{
    prepare_motion_program();
    register_ioports();
}
static inline status_code_t io_block(const char *text)
{
    char block[64];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
