#include "support/boot_host.h"

static unsigned changes;
static tool_id_t installed_tool;
static bool first_change_seen;
static status_code_t automatic_change(parser_state_t *parser)
{
    CHECK(parser == &gc_state);
    CHECK(hal.driver_cap.atc);
    CHECK(parser->tool_pending == (changes == 0 ? 3 : 4));
    installed_tool = parser->tool_pending;
    changes++;
    return Status_OK;
}
static void install_automatic_changer(void)
{
    hal.driver_cap.atc = true;
    hal.tool.change = automatic_change;
}
static void observe_automatic_changer(void)
{
    CHECK(hal.driver_cap.atc && hal.tool.change == automatic_change);
    if(boot_program[boot_reads] == CMD_RESET) {
        CHECK(changes == 1 && installed_tool == 3 && gc_state.tool->tool_id == 3);
        CHECK(!HOST_PARSER_FLAGS.tool_change && state_get() == STATE_IDLE);
        first_change_seen = true;
    }
}
int main(void)
{
    boot_during_init = install_automatic_changer;
    boot_before_read = observe_automatic_changer;
    boot_program = "T3M6\n\x18T4M6\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(first_change_seen && changes == 2);
    CHECK(installed_tool == 4 && gc_state.tool->tool_id == 4);
    CHECK(hal.tool.change == automatic_change && !HOST_PARSER_FLAGS.tool_change);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
