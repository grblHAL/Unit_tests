#include "support/program_end_host.h"

static unsigned program_end_messages;
static message_code_t (*original_feedback)(message_code_t);
static message_code_t observe_program_feedback(message_code_t message)
{
    if(message == Message_ProgramEnd) program_end_messages++;
    return original_feedback(message);
}

int main(void)
{
    prepare_program_end(false);
    hal.driver_cap.sd_card = true;
    char enable[] = "1", disable[] = "0", check[] = "$C";
    CHECK(settings_store_setting(Setting_SubroutineOptions, enable) == Status_OK);
    original_feedback = grbl.report.feedback_message;
    grbl.report.feedback_message = observe_program_feedback;
    CHECK(system_execute_line(check, hal.stream.write) == Status_OK);
    CHECK(state_get() == STATE_CHECK_MODE);
    CHECK(program_block("G1X1F100") == Status_OK);
    CHECK(program_block("M2") == Status_OK);
    CHECK(program_complete_calls == 1 && program_completion_check_mode);
    CHECK(program_end_messages == 0);
    CHECK(plan_get_current_block() == NULL && sys.position[X_AXIS] == 0);
    CHECK(settings_store_setting(Setting_SubroutineOptions, disable) == Status_OK);
    CHECK(program_block("M2") == Status_OK);
    CHECK(program_complete_calls == 2 && program_completion_check_mode);
    CHECK(program_end_messages == 1);
    CHECK(state_get() == STATE_CHECK_MODE && plan_get_current_block() == NULL);
    CHECK(sys.position[X_AXIS] == 0 && actual_coolant.mask == 0 && coolant_calls == 0);
    return EXIT_SUCCESS;
}
