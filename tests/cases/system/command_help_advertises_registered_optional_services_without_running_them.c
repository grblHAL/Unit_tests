#include "support/system_metadata_host.h"
#include "support/ioports_host.h"
static unsigned service_enumerations, service_status_reads, service_reboots;
static void enumerate_service_pins(bool low_level, pin_info_ptr callback, void *data)
{
    CHECK(!low_level);
    static xbar_t pin = {.pin = 2, .function = Output_StepX, .description = "Service pin"};
    service_enumerations++;
    callback(&pin, data);
}
static stepper_status_t read_service_status(bool reset)
{
    (void)reset;
    service_status_reads++;
    return (stepper_status_t){0};
}
static void reboot_service(void) { service_reboots++; }
int main(void)
{
    prepare_system_metadata();
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$PINS -") == NULL);
    CHECK(strstr(metadata_output, "$PINSTATE -") == NULL);
    CHECK(strstr(metadata_output, "$SDS -") == NULL);
    CHECK(strstr(metadata_output, "$REBOOT -") == NULL);
    hal.enumerate_pins = enumerate_service_pins;
    hal.stepper.status = read_service_status;
    hal.reboot = reboot_service;
    register_ioports();
    metadata_output[0] = '\0';
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$PINS - enumerate pin bindings.") != NULL);
    CHECK(strstr(metadata_output, "$PINSTATE - output auxiliary pin states.") != NULL);
    CHECK(strstr(metadata_output, "$SDS - output stepper driver status.") != NULL);
    CHECK(strstr(metadata_output, "$REBOOT - reboot (hard reset) controller.") != NULL);
    CHECK(service_enumerations == 0 && service_status_reads == 0 && service_reboots == 0);
    metadata_output[0] = '\0';
    CHECK(system_command("$PINS") == Status_OK);
    CHECK(strstr(metadata_output, "[PIN:2,X step,Service pin]" ASCII_EOL) != NULL);
    CHECK(service_enumerations == 2);
    CHECK(system_command("$SDS") == Status_OK);
    CHECK(service_status_reads == 1 && service_reboots == 0);
    return EXIT_SUCCESS;
}
