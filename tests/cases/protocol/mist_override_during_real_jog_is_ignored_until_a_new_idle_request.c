#include "support/jog_motion_host.h"
#include "override.h"

static coolant_state_t jog_coolant;
static unsigned jog_coolant_writes;
static void set_jog_coolant(coolant_state_t state)
{
    jog_coolant = state;
    jog_coolant_writes++;
}
static coolant_state_t get_jog_coolant(void) { return jog_coolant; }

int main(void)
{
    prepare_jog_motion();
    hal.coolant_cap.mist = true;
    hal.coolant.set_state = set_jog_coolant;
    hal.coolant.get_state = get_jog_coolant;
    CHECK(system_command("$J=G91X1F100") == Status_OK);
    CHECK(state_get() == STATE_JOG && plan_get_current_block() != NULL);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_MIST_TOGGLE));
    CHECK(protocol_exec_rt_system());
    CHECK(!gc_state.modal.coolant.mist && !jog_coolant.mist && jog_coolant_writes == 0);
    finish_jog_motion();
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(jog_coolant_writes == 0);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_MIST_TOGGLE));
    CHECK(protocol_exec_rt_system());
    CHECK(gc_state.modal.coolant.mist && jog_coolant.mist && jog_coolant_writes == 1);
    char stop[] = "M9";
    CHECK(gc_execute_block(stop) == Status_OK);
    CHECK(gc_state.modal.coolant.mask == 0 && jog_coolant.mask == 0 && jog_coolant_writes == 2);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
