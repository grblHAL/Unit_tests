#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    gc_override_values_t overrides = {.feed_rate = 100, .rapid_rate = 100, .spindle_rpm = {100}};
    CHECK(ngc_modal_state_save(&gc_state.modal, &overrides, 0, false));
    gc_state.modal.units_imperial = true;
    sys.cancel = true;
    CHECK(!ngc_modal_state_restore());
    CHECK(gc_state.modal.units_imperial);
    sys.cancel = false;
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
