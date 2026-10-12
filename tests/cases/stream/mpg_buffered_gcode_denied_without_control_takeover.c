#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    pendant_send_text("G20\n");
    engine_execute_tasks(STATE_IDLE);
    char expected[32];
    snprintf(expected, sizeof(expected), "error:%u" ASCII_EOL, (unsigned)Status_AccessDenied);
    CHECK(strcmp(pendant_output, expected) == 0);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(!sys.mpg_mode);
    return EXIT_SUCCESS;
}
