#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "G1F120X10Y5"; CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_Linear); NEAR(gc_state.feed_rate, 120); NEAR(gc_state.position[0], 10); NEAR(gc_state.position[1], 5);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
