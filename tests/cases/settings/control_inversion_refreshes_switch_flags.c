#include "support/settings_host.h"
#include "check.h"
static unsigned control_reads;
static control_signals_t enabled_control_switches(void)
{
    control_reads++;
    return (control_signals_t){.block_delete = true, .single_block = true, .stop_disable = true};
}

int main(void)
{
    prepare_settings_store();
    hal.signals_cap.reset = true;
    hal.control.get_state = enabled_control_switches;
    CHECK(store_setting(Setting_ControlInvertMask, "0") == Status_OK);
    CHECK(control_reads == 1);
    CHECK(sys.flags.block_delete_enabled);
    CHECK(sys.flags.single_block);
    CHECK(sys.flags.optional_stop_disable);
    return EXIT_SUCCESS;
}
