#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "G91"; CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.modal.distance_incremental); char absolute[] = "G90"; CHECK(gc_execute_block(absolute) == Status_OK); CHECK(!gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
