#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"
#include "state_machine.h"

int main(void)
{
    prepare_initialized_settings(2);
    gc_init(false);
    CHECK(state_get() == STATE_CHECK_MODE && gc_state.tool->tool_id == 0);
    tool_data_t tool = {.tool_id = 2, .offset.values = {1, 2, 3}};
    CHECK(host_save_tool(&tool));
    char block[] = "G43H2";
    CHECK(gc_execute_block(block) == Status_OK);
    for(unsigned axis = 0; axis < 3; axis++)
        NEAR(gc_state.modal.tool_length_offset[axis], (float)(axis + 1));
    const struct { const char *text; float offset[3]; } sequence[] = {
        {"G49", {0, 0, 0}},
        {"T2G43", {1, 2, 3}},
        {"G49", {0, 0, 0}},
        {"G43", {0, 0, 0}}
    };
    for(unsigned i = 0; i < sizeof(sequence) / sizeof(sequence[0]); i++) {
        char command[32];
        CHECK(strlen(sequence[i].text) < sizeof(command));
        strcpy(command, sequence[i].text);
        CHECK(gc_execute_block(command) == Status_OK);
        for(unsigned axis = 0; axis < 3; axis++) {
            NEAR(gc_state.modal.tool_length_offset[axis], sequence[i].offset[axis]);
        }
    }
    CHECK(gc_state.tool->tool_id == 0 && gc_state.tool_pending == 2);
    CHECK(state_get() == STATE_CHECK_MODE);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
