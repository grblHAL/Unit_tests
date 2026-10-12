#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    gc_modal_t modal = gc_state.modal;
    gc_override_values_t overrides = {.feed_rate = 80, .rapid_rate = 50};
    modal.units_imperial = true;
    CHECK(ngc_modal_state_save(&modal, &overrides, 123, false));
    modal.units_imperial = false;
    overrides.feed_rate = 100;
    gc_modal_snapshot_t *saved = ngc_modal_state_get();
    CHECK(saved != NULL);
    CHECK(saved->modal.units_imperial == true);
    CHECK(saved->override.feed_rate == 80);
    CHECK(saved->override.rapid_rate == 50);
    NEAR(saved->modal.feed_rate, 123);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
