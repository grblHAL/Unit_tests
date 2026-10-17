#include "support/boot_host.h"
#include "support/planner_allocation_host.h"
static void configure_constrained_driver(settings_t *current)
{
    CHECK(current == &settings);
    char blocks[] = "256";
    CHECK(settings_store_setting(Setting_PlannerBlocks, blocks) == Status_OK);
    planner_heap_limit = 129 * sizeof(plan_block_t);
}
int main(void)
{
    boot_during_setup = configure_constrained_driver;
    boot_program = "$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(planner_rejected_allocations > 0);
    CHECK(plan_get_buffer_size() >= 30 && plan_get_buffer_size() <= 128);
    CHECK(settings.planner_buffer_blocks == 256);
    CHECK(strstr(engine_output, "[MSG:Planner buffer size was reduced!]" ASCII_EOL));
    CHECK(strstr(engine_output, "[GC:") && strstr(engine_output, "error:") == NULL);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
