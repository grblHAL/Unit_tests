#include "support/spindle_slot_settings_host.h"
#include "support/tracked_malloc_host.h"
#include "report.h"
int main(void)
{
    prepare_settings_mapped_spindles();
    const char *expected = "[SPINDLE:0|0|1|DR|primary|1000.0,12000.0]" ASCII_EOL
                           "[SPINDLE:1|1|1|DR|secondary|1000.0,12000.0]" ASCII_EOL
                           "[SPINDLE:2|-|1|DR|auxiliary|1000.0,12000.0]" ASCII_EOL;
    unsigned configurations[3];
    memcpy(configurations, spindle_config_calls, sizeof(configurations));
    allocation_heap_reject = 1;
    observe_allocation_heap = true;
    CHECK(report_spindles(true) == Status_OK);
    observe_allocation_heap = false;
    CHECK(allocation_heap_calls == 1 && allocation_heap_failures == 1);
    CHECK(allocation_heap_frees == 0);
    CHECK(strcmp(engine_output, expected) == 0);
    CHECK(spindle_get_count() == 3 && spindle_get(0)->id == 0 && spindle_get(1)->id == 1);
    CHECK(memcmp(configurations, spindle_config_calls, sizeof(configurations)) == 0);
    engine_output[0] = '\0';
    allocation_heap_calls = allocation_heap_reject = 0;
    observe_allocation_heap = true;
    CHECK(report_spindles(true) == Status_OK);
    observe_allocation_heap = false;
    CHECK(allocation_heap_calls == 1 && allocation_heap_frees == 1);
    CHECK(strcmp(engine_output, expected) == 0);
    CHECK(memcmp(configurations, spindle_config_calls, sizeof(configurations)) == 0);
    for(unsigned id = 0; id < 3; id++) CHECK(spindle_output_calls[id] == 0);
    return EXIT_SUCCESS;
}
