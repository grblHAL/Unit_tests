#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "123";
    CHECK(gc_execute_block(block) == Status_ExpectedCommandLetter);
    return EXIT_SUCCESS;
}
