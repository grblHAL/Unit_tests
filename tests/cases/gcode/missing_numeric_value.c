#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "G1X";
    CHECK(gc_execute_block(block) == Status_BadNumberFormat);
    return EXIT_SUCCESS;
}
