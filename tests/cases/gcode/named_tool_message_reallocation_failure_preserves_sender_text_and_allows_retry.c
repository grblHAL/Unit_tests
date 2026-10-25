#include "support/m6_program_host.h"
#include "support/realloc_failure_host.h"

int main(void)
{
    prepare_m6_program();
    offset_entry.name = "End mill";
    fail_realloc = true;
    status_code_t status = m6_block("(MSG,Use backup label)T1M6");
    fail_realloc = false;
    CHECK(status == Status_OK && failed_realloc_calls == 1);
    CHECK(m6_change_calls == 1 && gc_state.tool == &offset_tool);
    CHECK(m6_changed_tool == &offset_tool && m6_driver_selected_tool == &offset_tool);
    CHECK(strstr(engine_output, "[MSG:Use backup label]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "End mill") == NULL);
    CHECK(gc_state.message == NULL);
    CHECK(m6_block("T0M6") == Status_OK);
    CHECK(m6_change_calls == 2 && gc_state.tool->tool_id == 0);
    engine_output[0] = 0;
    m6_expect_named_message = true;
    CHECK(m6_block("T1M6") == Status_OK);
    CHECK(m6_change_calls == 3 && gc_state.tool == &offset_tool);
    CHECK(strstr(engine_output, "[MSG:End mill]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "Use backup label") == NULL);
    CHECK(failed_realloc_calls == 1 && gc_state.message == NULL);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
