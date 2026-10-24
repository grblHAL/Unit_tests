#include "support/ioports_settings_host.h"

int main(void)
{
    CHECK(N_AXIS == 6 && U_AXIS == 3 && V_AXIS == 4);
    digital_pins[Port_Input][0].function = Input_MotorFaultU;
    digital_pins[Port_Input][1].function = Input_MotorFaultV;
    prepare_io_settings();
    hal.motor_fault_cap.a.mask = U_AXIS_BIT | V_AXIS_BIT;
    CHECK(store_io_setting(Setting_MotorFaultsInvert, "8") == Status_OK);
    ioport_setting_changed(Setting_MotorFaultsInvert);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    bool u_with_u_inverted = captured_input[0].inverted;
    bool v_with_u_inverted = captured_input[1].inverted;
    CHECK(store_io_setting(Setting_MotorFaultsInvert, "16") == Status_OK);
    ioport_setting_changed(Setting_MotorFaultsInvert);
    CHECK(input_config_calls[0] == 2 && input_config_calls[1] == 2);
    CHECK(!captured_input[0].debounce && !captured_input[1].debounce);
    CHECK(settings.motor_fault_invert.mask == V_AXIS_BIT);
    fprintf(stderr, "UVW motor-fault invert: U-only=(%u,%u) V-only=(%u,%u)\n",
        u_with_u_inverted, v_with_u_inverted, captured_input[0].inverted,
        captured_input[1].inverted);
    CHECK(u_with_u_inverted && !v_with_u_inverted);
    CHECK(!captured_input[0].inverted && captured_input[1].inverted);
    return EXIT_SUCCESS;
}
