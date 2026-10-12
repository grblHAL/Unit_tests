#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "N123G0X1"; CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.line_number == 123);
    return EXIT_SUCCESS;
}
