#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][0].function = Input_Probe;
    digital_pins[Port_Input][0].config = NULL;
    settings.probe.invert_probe_pin = true;
    settings.ioport.invert_in.mask = 0;
    ioport_setting_changed(Setting_InvertProbePin);
    CHECK(input_config_calls[0] == 0 && input_config_calls[1] == 0);
    CHECK(settings.ioport.invert_in.mask == 0);
    return EXIT_SUCCESS;
}
