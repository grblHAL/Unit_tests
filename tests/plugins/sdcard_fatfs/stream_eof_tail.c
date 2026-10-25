#include "file_stream_host.h"
int main(void)
{
    sd_prepare(true);
    fatfs_put_file("/TAIL.NC", "G1X1", 4);
    char name[] = "/TAIL.NC";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    char data[16];
    sd_read(data, sizeof(data));
    CHECK(!strcmp(data, "G1X1\n"));
    CHECK(!fs_busy() && sd_completions == 1 && sd_feedback == 1 &&
          hal.stream.read == sd_serial_read);
    return 0;
}
