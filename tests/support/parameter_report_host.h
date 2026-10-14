#pragma once
#include "support/report_host.h"
#include "nvs.h"
static memcpy_from_nvs_ptr parameter_read_previous;
static unsigned parameter_read_calls, parameter_fail_read, parameter_hook_calls, parameter_status_calls;
static status_code_t parameter_status;
static bool parameter_read(uint8_t *dest, uint32_t address, uint32_t size, bool checksum)
{
    parameter_read_calls++;
    if(parameter_fail_read && parameter_read_calls == parameter_fail_read) return false;
    return parameter_read_previous(dest, address, size, checksum);
}
static status_code_t parameter_status_report(status_code_t code)
{ parameter_status_calls++; parameter_status = code; return code; }
static void parameter_plugin_report(void)
{
    CHECK(strstr(engine_output, "[PRB:") != NULL);
    parameter_hook_calls++; hal.stream.write("[PLUGIN:ok]" ASCII_EOL);
}
static inline void prepare_parameter_report(void)
{
    prepare_report();
    parameter_read_previous = hal.nvs.memcpy_from_nvs;
    hal.nvs.memcpy_from_nvs = parameter_read;
    grbl.report.status_message = parameter_status_report;
    grbl.on_report_ngc_parameters = parameter_plugin_report;
}
