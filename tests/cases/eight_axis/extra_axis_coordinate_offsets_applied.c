#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    gc_state.modal.g5x_offset.data.coord.values[6] = 10;
    gc_state.modal.g5x_offset.data.coord.values[7] = 20;
    char block[] = "G1U1V2F100";
    CHECK(gc_execute_block(block) == Status_OK);
    NEAR(gc_state.position[6], 11);
    NEAR(gc_state.position[7], 22);
    return EXIT_SUCCESS;
}
