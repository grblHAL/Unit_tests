#include "support/cutter_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_parser(); CHECK(cutter_block("G41.1D6") == Status_GcodeUnsupportedCommand);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off); NEAR(gc_state.modal.cutter_comp.radius, 0);
    return EXIT_SUCCESS;
}
