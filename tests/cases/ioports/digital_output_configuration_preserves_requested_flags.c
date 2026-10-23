#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    gpio_out_config_t config = {.inverted = true, .open_drain = true};
    CHECK(ioport_digital_out_config(1, &config));
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 1);
    CHECK(captured_output[1].inverted && captured_output[1].open_drain);
    unsigned available = ioports_unclaimed(Port_Digital, Port_Output);
    output_config_result = false;
    CHECK(!ioport_digital_out_config(1, &config));
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 2);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == available);
    output_config_result = true;
    CHECK(ioport_digital_out_config(1, &config));
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 3);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == available);
    return EXIT_SUCCESS;
}
