#include "support/system_command_host.h"
int main(void)
{
    prepare_system_command();
    char offsets[] = "G10L2P1X12.5Y-4Z2";
    CHECK(gc_execute_block(offsets) == Status_OK);
    CHECK(system_command("$#=5221") == Status_OK);
    CHECK(system_command("$#=5222") == Status_OK);
    CHECK(system_command("$#=5223") == Status_OK);
    char extended[] = "G59.3";
    CHECK(gc_execute_block(extended) == Status_GcodeUnsupportedCommand);
    CHECK(system_command("$#=5381") == Status_OK);
    CHECK(strcmp(engine_output, "[PARAM:5221=12.5]" ASCII_EOL
        "[PARAM:5222=-4]" ASCII_EOL "[PARAM:5223=2]" ASCII_EOL
        "[PARAM:5381=0]" ASCII_EOL) == 0);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    CHECK(plan_get_current_block() == NULL);
    CHECK(sys.position[X_AXIS] == 0 && sys.position[Y_AXIS] == 0 && sys.position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
