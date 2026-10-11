#pragma once
#include "support/report_host.h"
#include "nvs_buffer.h"
static atc_status_t build_atc_state;
static unsigned build_options_calls;
static bool build_options_phase[4], build_plugin_output;
static atc_status_t get_build_atc_state(void) { return build_atc_state; }
static bool build_suspend(bool suspend) { return suspend; }
static uint32_t build_free_memory(void) { return 12288; }
static void build_options(bool new_options)
{
    CHECK(build_options_calls < 4);
    build_options_phase[build_options_calls++] = new_options;
    if(build_plugin_output)
        hal.stream.write(new_options ? ",FIXTURE" : "[PLUGIN:fixture]" ASCII_EOL);
}
static inline void prepare_build_report(void)
{
    prepare_report();
    hal.tool.atc_get_state = get_build_atc_state;
    grbl.on_report_options = build_options;
}
static inline void build_report(bool extended)
{
    char text[] = "fixture";
    report_build_info(text, extended);
}
