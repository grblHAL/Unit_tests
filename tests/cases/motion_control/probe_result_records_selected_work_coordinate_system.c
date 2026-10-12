#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    char block[] = "G55";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G55);
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Found);
    CHECK(sys.probe_coordsys_id == CoordinateSystem_G55);
    CHECK(sys.probe_position[X_AXIS] == 40);
    return EXIT_SUCCESS;
}
