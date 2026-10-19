#include "support/report_host.h"
static unsigned clear_calls;
static status_code_t clear_sender_message(char *message)
{
    CHECK(message != NULL && message[0] == '\0');
    clear_calls++;
    return Status_OK;
}
int main(void)
{
    prepare_report();
    grbl.on_gcode_message = clear_sender_message;
    CHECK(grbl.report.feedback_message(Message_None) == Message_None);
    CHECK(clear_calls == 1);
    CHECK(grbl.report.feedback_message(Message_ProgramEnd) == Message_ProgramEnd);
    CHECK(clear_calls == 1);
    CHECK(strstr(engine_output, "[MSG:Pgm End]") != NULL);
    grbl.on_gcode_message = NULL;
    CHECK(grbl.report.feedback_message(Message_None) == Message_None);
    CHECK(clear_calls == 1);
    return EXIT_SUCCESS;
}
