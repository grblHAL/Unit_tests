#include "support/boot_host.h"
static bool offsets_seen;
static void observe_offsets_before_reset(void)
{
    if(boot_program[boot_reads] != CMD_RESET) return;
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G55);
    NEAR(gc_state.g92_offset.coord.values[X_AXIS], -12);
    offsets_seen = true;
}
int main(void)
{
    boot_before_read = observe_offsets_before_reset;
    boot_program = "$676=2\nG55\nG92X12\nG91\n\x18$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(offsets_seen);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    NEAR(gc_state.g92_offset.coord.values[X_AXIS], -12);
    CHECK(!gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
