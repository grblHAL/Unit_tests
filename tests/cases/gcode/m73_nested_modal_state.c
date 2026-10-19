#include "support/incoming_gcode_host.h"
static unsigned snapshot_calls;
static status_code_t nested_auto_snapshot(macro_id_t id, line_number_t line, parameter_words_t words, uint32_t repeats)
{
    (void)line; (void)words; (void)repeats; snapshot_calls++;
    CHECK(incoming_block("M73") == Status_OK);
    if(id == 100) {
        CHECK(incoming_block("G91G18") == Status_OK);
        CHECK(incoming_block("G65P101") == Status_OK);
        CHECK(gc_state.modal.distance_incremental && gc_state.modal.plane_select == PlaneSelect_ZX);
    } else {
        CHECK(id == 101);
        CHECK(incoming_block("G90G19") == Status_OK);
    }
    return Status_OK;
}
int main(void)
{
    prepare_incoming_parser();
    grbl.on_macro_execute = nested_auto_snapshot;
    CHECK(incoming_block("G90G17") == Status_OK);
    CHECK(incoming_block("G65P100") == Status_OK);
    CHECK(!gc_state.modal.distance_incremental && gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(ngc_call_level() == 0 && snapshot_calls == 2);
    return EXIT_SUCCESS;
}
