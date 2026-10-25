#include "support/settings_initialized_host.h"
#include "report.h"
static void table_modal_block(const char *text)
{
    char block[48];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    CHECK(gc_execute_block(block) == Status_OK);
    engine_output[0] = '\0';
    report_gcode_modes(hal.stream.write);
}
int main(void)
{
    prepare_initialized_settings(2);
    gc_init(false);
    tool_data_t base = {.tool_id = 2, .offset.values = {1, 2, 3}};
    tool_data_t additional = {.tool_id = 3, .offset.values = {4, 5, 6}};
    CHECK(host_save_tool(&base) && host_save_tool(&additional));
    table_modal_block("G43H2");
    CHECK(strstr(engine_output, " G43 ") != NULL);
    CHECK(strstr(engine_output, " G43.1 ") == NULL && strstr(engine_output, " G43.2 ") == NULL);
    for(unsigned axis = 0; axis < 3; axis++)
        NEAR(gc_state.modal.tool_length_offset[axis], (float)(axis + 1));
    table_modal_block("G43.2H3");
    CHECK(strstr(engine_output, " G43.2 ") != NULL && strstr(engine_output, " G43.1 ") == NULL);
    for(unsigned axis = 0; axis < 3; axis++)
        NEAR(gc_state.modal.tool_length_offset[axis], (float)(5 + 2 * axis));
    table_modal_block("G49");
    CHECK(strstr(engine_output, " G49 ") != NULL && strstr(engine_output, " G43") == NULL);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], 0);
    return EXIT_SUCCESS;
}
