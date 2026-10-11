#pragma once
#include "support/system_command_host.h"
#include "alarms.h"
#include "errors.h"
static char metadata_output[131072];
static void metadata_write(const char *text)
{
    CHECK(strlen(metadata_output) + strlen(text) < sizeof(metadata_output));
    strcat(metadata_output, text);
}
static bool metadata_char(uint8_t c) { char text[] = {(char)c, 0}; metadata_write(text); return true; }
static inline void prepare_system_metadata(void)
{
    prepare_system_command();
    hal.stream.write = hal.stream.write_all = metadata_write;
    hal.stream.write_char = metadata_char;
    grbl.on_get_alarms = alarms_get_details;
    grbl.on_get_errors = errors_get_details;
    grbl.on_report_command_help = system_command_help;
}
