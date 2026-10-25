#include "support/ioports_settings_host.h"
int main(void)
{
    prepare_io_settings();
    unsigned inputs = ioports_unclaimed(Port_Digital, Port_Input);
    unsigned outputs = ioports_unclaimed(Port_Digital, Port_Output);
    CHECK(store_io_setting(Setting_AxisStepsPerMM, "100") == Status_OK);
    ioport_setting_changed(Setting_AxisStepsPerMM);
    for(unsigned port = 0; port < 2; port++)
        CHECK(input_config_calls[port] == 0 && output_config_calls[port] == 0);
    CHECK(settings.ioport.invert_in.mask == 0 && settings.ioport.invert_out.mask == 0);
    CHECK(settings.ioport.pullup_disable_in.mask == 0 && settings.ioport.od_enable_out.mask == 0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == inputs);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == outputs);
    NEAR(settings.axis[X_AXIS].steps_per_mm, 100);
    return EXIT_SUCCESS;
}
