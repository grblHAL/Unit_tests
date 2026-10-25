#include "support/multiple_probe_report_host.h"
#include "state_machine.h"
#include "protocol.h"
#include "ngc_params.h"

static void request_probe_status(void)
{
    engine_output[0] = 0;
    CHECK(protocol_enqueue_realtime_command(CMD_STATUS_REPORT));
    CHECK(protocol_exec_rt_system());
}
int main(void)
{
    prepare_multiple_probe_report();
    state_set(STATE_IDLE);
    sys.cold_start = false;
    sys.driver_started = true;
    CHECK(!settings.probe.enable_protection);
    request_probe_status();
    char select_toolsetter[] = "G65P5Q1";
    CHECK(gc_execute_block(select_toolsetter) == Status_OK);
    CHECK(hal.probe.get_state().probe_id == Probe_Toolsetter);
    CHECK(hal.stream.report.flags.probe_id && !hal.stream.report.flags.probe_protect);
    request_probe_status();
    CHECK(strstr(engine_output, "|P:1") != NULL);
    CHECK(strstr(engine_output, "|P:1,P") == NULL);
    CHECK(!hal.probe.get_state().irq_enabled && !hal.probe.get_state().is_probing);
    request_probe_status();
    CHECK(strstr(engine_output, "|P:") == NULL);
    CHECK(hal.probe.get_state().probe_id == Probe_Toolsetter);
    CHECK(ngc_call_level() == 0 && state_get() == STATE_IDLE);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == 0);
    return EXIT_SUCCESS;
}
