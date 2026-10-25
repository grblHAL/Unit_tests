#include "support/system_command_host.h"
static stepper_status_t driver_status;
static unsigned status_reads;
static stepper_status_t read_driver_status(bool reset)
{
    CHECK(!reset);
    status_reads++;
    return driver_status;
}
int main(void)
{
    prepare_system_command();
    hal.stepper.status = read_driver_status;
    hal.motor_warning_cap.a.mask = X_AXIS_BIT;
    hal.motor_fault_cap.a.mask = Z_AXIS_BIT;
    driver_status.warning.state = true;
    driver_status.warning.details.a.mask = X_AXIS_BIT;
    CHECK(system_command("$SDS") == Status_OK);
    CHECK(strcmp(engine_output, "[MOTORWARNING:X]" ASCII_EOL) == 0);
    engine_output[0] = '\0';
    driver_status = (stepper_status_t){0};
    driver_status.fault.state = true;
    driver_status.fault.details.a.mask = Z_AXIS_BIT;
    CHECK(system_command("$SDS") == Status_OK);
    CHECK(strcmp(engine_output, "[MOTORFAULT:Z]" ASCII_EOL) == 0);
    engine_output[0] = '\0';
    driver_status = (stepper_status_t){0};
    CHECK(system_command("$SDS") == Status_OK);
    CHECK(engine_output[0] == '\0' && status_reads == 3);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(plan_get_current_block() == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == 0);
    return EXIT_SUCCESS;
}
