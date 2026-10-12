#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    CHECK(!sys.ioinit_pending);
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(input_config_calls[0] == 0 && input_config_calls[1] == 0);
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 0);
    return EXIT_SUCCESS;
}
