#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    coord_system_data_t first = {0}, second = {0};
    first.coord.values[X_AXIS] = 12;
    second.coord.values[X_AXIS] = 34;
    settings_write_coord_data((coord_system_id_t)0, &first);
    settings_write_coord_data((coord_system_id_t)1, &second);
    gc_override_values_t overrides = {.feed_rate = 100, .rapid_rate = 100, .spindle_rpm = {100}};
    CHECK(ngc_modal_state_save(&gc_state.modal, &overrides, 0, false));
    char changed[] = "G55";
    CHECK(gc_execute_block(changed) == Status_OK);
    NEAR(gc_state.modal.g5x_offset.data.coord.values[X_AXIS], 34);
    CHECK(ngc_modal_state_restore());
    CHECK(gc_state.modal.g5x_offset.id == 0);
    NEAR(gc_state.modal.g5x_offset.data.coord.values[X_AXIS], 12);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
