#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    pendant_send_text("$13\n");
    engine_execute_tasks(STATE_IDLE);
    CHECK(strcmp(pendant_output, "$13=0" ASCII_EOL "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
