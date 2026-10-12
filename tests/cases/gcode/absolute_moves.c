#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char first[] = "G0X10"; CHECK(gc_execute_block(first) == Status_OK);
    char next[] = "G0X3"; CHECK(gc_execute_block(next) == Status_OK); NEAR(gc_state.position[0], 3);
    return EXIT_SUCCESS;
}
