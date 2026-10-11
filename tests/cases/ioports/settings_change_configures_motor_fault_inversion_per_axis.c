#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][0].function = Input_MotorFaultX;
    digital_pins[Port_Input][1].function = Input_MotorFaultY;
    settings.motor_fault_invert.mask = 1;
    settings.ioport.invert_in.mask = 2;
    ioport_setting_changed(Setting_MotorFaultsInvert);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    CHECK(captured_input[0].inverted && !captured_input[1].inverted);
    CHECK(!captured_input[0].debounce && !captured_input[1].debounce);
    CHECK((settings.ioport.invert_in.mask & 3) == 1);
    return EXIT_SUCCESS;
}
