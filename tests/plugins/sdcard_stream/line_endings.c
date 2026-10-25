#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    char name[] = "/mixed.ngc";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    char data[32];
    sd_read(data, sizeof(data));
    for (size_t i = 0; i < strlen(data); i++)
        fprintf(stderr, "%02X ", (unsigned char)data[i]);
    fprintf(stderr, "\n");
    CHECK(!strcmp(data, "A\rB\nC\rD\n"));
    CHECK(sd_completions == 1 && !fs_busy());
    return 0;
}
