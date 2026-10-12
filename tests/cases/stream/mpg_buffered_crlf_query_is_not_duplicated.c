#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    pendant_send_text("$G\r\n");
    engine_execute_tasks(STATE_IDLE);
    char *first = strstr(pendant_output, "[GC:");
    CHECK(first != NULL);
    CHECK(strstr(first + 4, "[GC:") == NULL);
    char *ack = strstr(pendant_output, "ok" ASCII_EOL);
    CHECK(ack != NULL);
    CHECK(strstr(ack + 4, "ok" ASCII_EOL) == NULL);
    return EXIT_SUCCESS;
}
