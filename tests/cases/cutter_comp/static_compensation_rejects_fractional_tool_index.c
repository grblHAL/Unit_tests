#include "support/cutter_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_parser(); CHECK(cutter_block("G41D1.5") == Status_GcodeCommandValueNotInteger);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off);
    return EXIT_SUCCESS;
}
