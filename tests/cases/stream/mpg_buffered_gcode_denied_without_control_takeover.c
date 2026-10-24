#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    pendant_send_text("G20\n");
    engine_execute_tasks(STATE_IDLE);
    char expected[32];
    snprintf(expected, sizeof(expected), "error:%u" ASCII_EOL, (unsigned)Status_AccessDenied);
    CHECK(strcmp(pendant_output, expected) == 0);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(!sys.mpg_mode);
    pendant_output[0] = primary_output[0] = '\0';
    settings.status_report.pin_state = true;
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    CHECK(!hal.stream.report.flags.cycle_start);
    CHECK(stream_mpg_check_enable(CMD_FEED_HOLD));
    CHECK(sys.rt_exec_state & EXEC_FEED_HOLD);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    CHECK(!hal.stream.report.flags.cycle_start);
    CHECK(pendant_output[0] == '\0' && primary_output[0] == '\0');
    pendant_send_text("$13\n");
    engine_execute_tasks(STATE_IDLE);
    CHECK(strcmp(pendant_output, "$13=0" ASCII_EOL "ok" ASCII_EOL) == 0);
    CHECK(primary_output[0] == '\0');
    CHECK(!sys.mpg_mode && hal.stream.read == primary_input);
    return EXIT_SUCCESS;
}
