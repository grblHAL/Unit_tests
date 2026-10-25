#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    char name[] = "/mixed.ngc";
    CHECK(sd_command("F<", name) == Status_OK);
    for (size_t i = 0; i < strlen(sd_output); i++)
        fprintf(stderr, "%02X ", (unsigned char)sd_output[i]);
    fprintf(stderr, "\n");
    CHECK(!strcmp(sd_output, "A\r\nB\r\nC\r\nD\r\n"));
    CHECK(!fs_busy() && sd_statuses == 0 && hal.stream.read == sd_serial_read);
    return 0;
}
