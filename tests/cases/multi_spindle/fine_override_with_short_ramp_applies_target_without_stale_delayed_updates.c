#include "support/paired_pwm_program_host.h"
int main(void)
{
    prepare_paired_pwm_program();
    char delay[] = "0.5";
    CHECK(settings_store_setting(Setting_SpindleOnDelay, delay) == Status_OK);
    CHECK(spindle_program_block("M3S6000$0") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    spindle_ptrs_t *primary = spindle_get(0);
    CHECK(pair_output[0] == primary->get_pwm(primary, 6000));
    CHECK(spindle_program_block("M3S1000$0") == Status_OK);
    CHECK(pair_output[0] == primary->get_pwm(primary, 1000));
    CHECK(settings.spindle.on_delay == 500 && primary->param->option.ramp_up);
    unsigned secondary_calls = pair_calls[1];
    const uint8_t commands[] = {CMD_OVERRIDE_SPINDLE_FINE_PLUS, CMD_OVERRIDE_SPINDLE_FINE_MINUS};
    const unsigned percentages[] = {101, 100};
    for(unsigned change = 0; change < 2; change++) {
        unsigned before = pair_calls[0];
        CHECK(protocol_enqueue_realtime_command(commands[change]));
        CHECK(protocol_exec_rt_system());
        float expected = 1000 * (float)percentages[change] / 100;
        CHECK(primary->param->override_pct == percentages[change]);
        fprintf(stderr, "Fine override %u: programmed=%.9g overridden=%.9g output=%u calls=%u\n", percentages[change], primary->param->rpm, primary->param->rpm_overridden, (unsigned)pair_output[0], pair_calls[0] - before);
        CHECK(fabsf(primary->param->rpm - 1000) < .01f);
        CHECK(fabsf(primary->param->rpm_overridden - expected) < .01f);
        CHECK(pair_calls[0] == before + 1);
        CHECK(pair_output[0] == primary->get_pwm(primary, expected));
        for(unsigned tick = 0; tick < 8; tick++) {
            engine_ticks += DWELL_TIME_STEP;
            engine_execute_tasks(STATE_IDLE);
        }
        CHECK(pair_calls[0] == before + 1);
        CHECK(pair_output[0] == primary->get_pwm(primary, expected));
        CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
        CHECK(pair_calls[1] == secondary_calls && !actual_spindle_states[1].on);
    }
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
