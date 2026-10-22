#include "support/cutter_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("G41.1D6") == Status_OK); CHECK(cutter_block("G40") == Status_OK);
    CHECK(cutter_block("G1X3F100") == Status_CutterCompConflict);
    NEAR(gc_state.position[X_AXIS], 0); CHECK(HOST_PARSER_FLAGS.ccomp_off);
    return EXIT_SUCCESS;
}
