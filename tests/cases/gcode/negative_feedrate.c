#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "F-100";
    CHECK(gc_execute_block(block) == Status_NegativeValue); NEAR(gc_state.feed_rate, 0);
    return EXIT_SUCCESS;
}
