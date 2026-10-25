#include "support/ioports_settings_host.h"

int main(void)
{
    CHECK(N_AXIS == 6 && W_AXIS == 5);
    digital_pins[Port_Input][0].function = Input_MotorFaultW;
    digital_pins[Port_Input][1].function = Input_MotorFaultX;
    prepare_io_settings();
    hal.motor_fault_cap.a.mask = W_AXIS_BIT | X_AXIS_BIT;
    CHECK(store_io_setting(Setting_MotorFaultsInvert, "1") == Status_OK);
    ioport_setting_changed(Setting_MotorFaultsInvert);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    CHECK(captured_input[1].inverted && !captured_input[1].debounce);
    bool w_with_x_inverted = captured_input[0].inverted;
    CHECK(store_io_setting(Setting_MotorFaultsInvert, "32") == Status_OK);
    ioport_setting_changed(Setting_MotorFaultsInvert);
    CHECK(input_config_calls[0] == 2 && input_config_calls[1] == 2);
    CHECK(!captured_input[1].inverted && !captured_input[0].debounce);
    CHECK(settings.motor_fault_invert.mask == W_AXIS_BIT);
    fprintf(stderr, "UVW motor-fault W invert: X-only=%u W-only=%u\n",
        w_with_x_inverted, captured_input[0].inverted);
    CHECK(!w_with_x_inverted);
    CHECK(captured_input[0].inverted);
    return EXIT_SUCCESS;
}
