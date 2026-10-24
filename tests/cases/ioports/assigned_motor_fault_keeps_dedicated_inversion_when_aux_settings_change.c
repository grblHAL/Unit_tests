#include "support/ioports_settings_host.h"
static bool assign_fault(xbar_t *pin, pin_function_t function)
{
    CHECK(pin == &digital_pins[Port_Input][0] && function == Input_MotorFaultX);
    return true;
}
int main(void)
{
    prepare_io_settings();
    hal.motor_fault_cap.a.mask = X_AXIS_BIT;
    xbar_t *fault = hal.port.get_pin_info(Port_Digital, Port_Input, 0);
    fault->set_function = assign_fault;
    fault->mode.debounce = true;
    CHECK(ioport_set_function(fault, Input_MotorFaultX, (driver_caps_t){0}));
    CHECK(ioports_available(Port_Digital, Port_Input) == 1);
    CHECK(store_io_setting(Setting_MotorFaultsInvert, "1") == Status_OK);
    // The board notifies the shared pin configurator after its fault setting changes.
    ioport_setting_changed(Setting_MotorFaultsInvert);
    CHECK(captured_input[0].inverted && !captured_input[0].debounce);
    unsigned calls = input_config_calls[0];
    CHECK(store_io_setting(Settings_IoPort_InvertIn, "2") == Status_OK);
    CHECK(input_config_calls[0] == calls && captured_input[0].inverted);
    CHECK(captured_input[1].inverted);
    CHECK(settings.motor_fault_invert.mask == X_AXIS_BIT);
    CHECK(store_io_setting(Setting_MotorFaultsInvert, "0") == Status_OK);
    ioport_setting_changed(Setting_MotorFaultsInvert);
    CHECK(!captured_input[0].inverted && !captured_input[0].debounce);
    CHECK(captured_input[1].inverted && fault->function == Input_MotorFaultX);
    return EXIT_SUCCESS;
}
