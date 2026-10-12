#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "G2F100X10R1";
    CHECK(gc_execute_block(block) == Status_GcodeArcRadiusError);
    return EXIT_SUCCESS;
}
