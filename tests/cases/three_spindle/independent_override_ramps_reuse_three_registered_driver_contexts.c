#include "support/three_pwm_program_host.h"

int main(void)
{
    prepare_three_pwm_program();
    const char *start[] = {"M3S6000$0", "M4S5000$1", "M3S4000$2"};
    for(unsigned id = 0; id < 3; id++) {
        CHECK(spindle_program_block(start[id]) == Status_OK);
        CHECK(spindle_get(id)->param->option.ramp_up);
    }
    const unsigned percentages[2][3] = {{120, 80, 110}, {100, 100, 100}};
    const float programmed[] = {6000, 5000, 4000};
    for(unsigned pass = 0; pass < 2; pass++) {
        unsigned before[3];
        float targets[3];
        for(unsigned id = 0; id < 3; id++) {
            before[id] = triple_calls[id];
            float expected = programmed[id] * percentages[pass][id] / 100;
            targets[id] = spindle_set_override(spindle_get(id), percentages[pass][id]);
            CHECK(fabsf(targets[id] - expected) < .01f);
        }
        for(unsigned tick = 0; tick < 16; tick++) {
            engine_ticks += DWELL_TIME_STEP;
            engine_execute_tasks(STATE_IDLE);
        }
        for(unsigned id = 0; id < 3; id++) {
            spindle_ptrs_t *spindle = spindle_get(id);
            CHECK(spindle->id == (spindle_id_t)id && actual_spindle_states[id].on);
            CHECK(actual_spindle_states[id].ccw == (id == 1));
            CHECK(triple_calls[id] > before[id]);
            CHECK(triple_output[id] == triple_get_pwm(spindle, targets[id]));
            CHECK(fabsf(spindle->param->rpm - programmed[id]) < .01f);
            before[id] = triple_calls[id];
        }
        for(unsigned tick = 0; tick < 8; tick++) {
            engine_ticks += DWELL_TIME_STEP;
            engine_execute_tasks(STATE_IDLE);
        }
        for(unsigned id = 0; id < 3; id++) CHECK(triple_calls[id] == before[id]);
    }
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    for(unsigned id = 0; id < 3; id++) CHECK(!actual_spindle_states[id].on);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
