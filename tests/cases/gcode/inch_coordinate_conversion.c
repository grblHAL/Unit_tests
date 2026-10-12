#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "G20G0X1"; CHECK(gc_execute_block(block) == Status_OK);
    NEAR(gc_state.position[0], 25.4f); CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
