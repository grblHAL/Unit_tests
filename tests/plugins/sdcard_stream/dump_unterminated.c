#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    char name[] = "/readme.bin";
    CHECK(sd_command("F<", name) == Status_OK);
    CHECK(!strcmp(sd_output, "BIN" ASCII_EOL));
    CHECK(!fs_busy() && hal.stream.read == sd_serial_read);
    return 0;
}
