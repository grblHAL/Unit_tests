#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "G999";
    CHECK(gc_execute_block(block) == Status_GcodeUnsupportedCommand);
    return EXIT_SUCCESS;
}
