#include "support/ioports_settings_host.h"
int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][0].function = Input_MotorFaultX;
    digital_pins[Port_Input][0].mode.debounce = true;
    settings.motor_fault_invert.mask = X_AXIS_BIT;
    settings.ioport.invert_in.mask = 0;
    sys.ioinit_pending = true;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(input_config_calls[0] == 1);
    CHECK(captured_input[0].inverted && !captured_input[0].debounce);
    CHECK(!captured_input[1].inverted);
    return EXIT_SUCCESS;
}
