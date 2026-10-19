#include "support/system_command_host.h"
int main(void)
{
    prepare_system_command();
    char incremental[] = "G91";
    CHECK(gc_execute_block(incremental) == Status_OK);
    CHECK(system_command("$#=_ijk_absolute_mode") == Status_OK);
    CHECK(system_command("$#=_adaptive_feed") == Status_OK);
    CHECK(system_command("$#=_ccomp") == Status_OK);
    CHECK(strstr(engine_output, "[PARAM:_ijk_absolute_mode=0]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[PARAM:_adaptive_feed=0]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[PARAM:_ccomp=400]" ASCII_EOL) != NULL);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
