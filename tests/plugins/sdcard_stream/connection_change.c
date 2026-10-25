#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    char name[] = "/job.nc";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    stream_set_file(NULL, sd_serial_read);
    grbl.on_stream_changed();
    sd_state = STATE_CYCLE;
    sd_run_tasks();
    CHECK(!fs_busy() && sys.flags.keep_input && (sys.rt_exec_state & EXEC_STOP));
    CHECK(sd_state == STATE_IDLE && strstr(sd_output, "connection change"));
    return 0;
}
