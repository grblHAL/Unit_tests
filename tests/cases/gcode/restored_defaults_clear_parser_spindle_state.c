#include "support/parser_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_parser_settings();
    gc_state.modal.spindle[0].state.on = true;
    gc_state.modal.spindle[0].rpm = 500;
    settings_changed_flags_t flags = {.restore_defaults = true};
    grbl.on_settings_changed(&settings, flags);
    CHECK(parser_settings_calls == 1);
    CHECK(parser_changed_flags.spindle == flags.spindle);
    CHECK(parser_changed_flags.restore_defaults == flags.restore_defaults);
    CHECK(gc_state.modal.spindle[0].state.on == false);
    NEAR(gc_state.modal.spindle[0].rpm, 0.0f);
    return EXIT_SUCCESS;
}
