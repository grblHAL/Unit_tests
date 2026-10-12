#include "support/cutter_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_parser(); CHECK(cutter_block("G40") == Status_OK);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off); CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
