#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    settings.ioport.invert_in.mask = 2;
    settings.ioport.invert_out.mask = 1;
    settings.ioport.od_enable_out.mask = 2;
    sys.ioinit_pending = true;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    CHECK(output_config_calls[0] == 1 && output_config_calls[1] == 1);
    CHECK(!captured_input[0].inverted && captured_input[1].inverted);
    CHECK(captured_output[0].inverted && !captured_output[1].inverted);
    CHECK(!captured_output[0].open_drain && captured_output[1].open_drain);
    return EXIT_SUCCESS;
}
