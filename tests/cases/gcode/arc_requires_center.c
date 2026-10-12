#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "G2F100X10";
    CHECK(gc_execute_block(block) == Status_GcodeNoOffsetsInPlane);
    return EXIT_SUCCESS;
}
