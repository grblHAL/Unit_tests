#include "support/engine_host.h"
#include "check.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G59.3";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G59_3);
    return EXIT_SUCCESS;
}
