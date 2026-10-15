#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#if NGC_PARAMETERS_ENABLE || NGC_EXPRESSIONS_ENABLE
#error This case requires the parameters-disabled configuration
#endif
int main(void)
{
    engine_parser_prepare();
    const char *commands[] = {"M70", "M71", "M72", "M73"};
    for(unsigned i = 0; i < 4; i++) {
        char block[8]; strcpy(block, commands[i]);
        CHECK(gc_execute_block(block) == Status_GcodeUnsupportedCommand);
        CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
        CHECK(plan_get_current_block() == NULL);
        NEAR(gc_state.position[X_AXIS], 0);
    }
    return EXIT_SUCCESS;
}
