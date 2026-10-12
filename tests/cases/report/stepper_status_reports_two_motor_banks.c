#include "support/report_host.h"
#include "check.h"
static stepper_status_t read_motor_report(bool reset)
{
    CHECK(!reset);
    stepper_status_t status = {0};
    status.warning.state = status.fault.state = true;
    status.warning.details.a.mask = 1;
    status.warning.details.b.mask = 2;
    status.fault.details.a.mask = 4;
    status.fault.details.b.mask = 1;
    return status;
}

int main(void)
{
    prepare_report();
    hal.stepper.status = read_motor_report;
    CHECK(report_stepper_status(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[MOTORWARNING:X,Y]" ASCII_EOL "[MOTORFAULT:Z,X]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
