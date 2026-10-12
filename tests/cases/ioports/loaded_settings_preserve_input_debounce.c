#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][1].mode.debounce = true;
    sys.ioinit_pending = true;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(captured_input[1].debounce && !captured_input[0].debounce);
    CHECK(captured_input[1].pull_mode == PullMode_Up);
    return EXIT_SUCCESS;
}
