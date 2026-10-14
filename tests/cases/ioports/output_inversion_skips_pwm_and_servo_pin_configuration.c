#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Output][0].mode.pwm = true;
    digital_pins[Port_Output][1].mode.servo_pwm = true;
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "3") == Status_OK);
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 0);
    CHECK(settings.ioport.invert_out.mask == 3);
    return EXIT_SUCCESS;
}
