#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(!settings.flags.report_inches);
    pendant_send_text("$13\n");
    CHECK(pendant_output[0] == '\0');
    engine_execute_tasks(STATE_IDLE);
    CHECK(strcmp(pendant_output, "$13=0" ASCII_EOL "ok" ASCII_EOL) == 0);

    // The MPG sends another command only after receiving the previous response.
    pendant_output[0] = '\0';
    pendant_send_text("$G\n");
    CHECK(pendant_output[0] == '\0');
    engine_execute_tasks(STATE_IDLE);
    CHECK(strstr(pendant_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    char *ack = strstr(pendant_output, "ok" ASCII_EOL);
    CHECK(ack != NULL);
    CHECK(strstr(ack + strlen("ok" ASCII_EOL), "ok" ASCII_EOL) == NULL);
    for(unsigned blank = 0; blank < 2; blank++) {
        pendant_output[0] = '\0';
        pendant_send_text("\n");
        CHECK(pendant_output[0] == '\0');
        engine_execute_tasks(STATE_IDLE);
        CHECK(strcmp(pendant_output, "ok" ASCII_EOL) == 0);
    }
    pendant_output[0] = '\0';
    pendant_send_text("$13\n");
    engine_execute_tasks(STATE_IDLE);
    CHECK(strcmp(pendant_output, "$13=0" ASCII_EOL "ok" ASCII_EOL) == 0);
    CHECK(!sys.mpg_mode && hal.stream.read == primary_input);
    return EXIT_SUCCESS;
}
