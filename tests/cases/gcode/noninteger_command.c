#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "M3.5";
    CHECK(gc_execute_block(block) == Status_GcodeCommandValueNotInteger);
    return EXIT_SUCCESS;
}
