#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char original[] = "G99";
    CHECK(gc_execute_block(original) == Status_OK);
    gc_override_values_t overrides = {.feed_rate = 100, .rapid_rate = 100, .spindle_rpm = {100}};
    CHECK(ngc_modal_state_save(&gc_state.modal, &overrides, 0, false));
    char changed[] = "G98";
    CHECK(gc_execute_block(changed) == Status_OK);
    CHECK(ngc_modal_state_restore());
    CHECK(gc_state.modal.retract_mode == CCRetractMode_RPos);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
