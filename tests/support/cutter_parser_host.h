#pragma once
#include "support/ngc_tool_file_host.h"
static inline void prepare_cutter_parser(void)
{
    vfs_file_t *file = prepare_ngc_tool_file(); stream_redirect_close(file);
    CHECK(hal.stream.file == NULL);
}
static inline status_code_t cutter_block(const char *text)
{ char block[96]; CHECK(strlen(text) < sizeof(block)); strcpy(block, text); return gc_execute_block(block); }
