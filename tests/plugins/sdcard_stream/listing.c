#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    CHECK(sd_command("F", NULL) == Status_OK);
    CHECK(strstr(sd_output, "job.nc") && strstr(sd_output, "mixed.ngc") &&
          !strstr(sd_output, "readme.bin") && !strstr(sd_output, "hidden.nc"));
    sd_clear_output();
    CHECK(sd_command("F+", NULL) == Status_OK);
    CHECK(strstr(sd_output, "readme.bin") && !strstr(sd_output, "hidden.nc"));
    return 0;
}
