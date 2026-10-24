#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(vi_command("0,1") == Status_OK);
    const char *invalid[] = {"2,1", "0,2", "0:1", "0,1x", "word", "0,", ""};
    for (unsigned i = 0; i < sizeof(invalid) / sizeof(invalid[0]); i++)
    {
        CHECK(vi_command(invalid[i]) != Status_OK);
        CHECK(virtual_inputs_get().mask == 1);
    }
    return 0;
}
