#include "support/boot_host.h"
int main(void)
{
    boot_program = "$12=0.1\n$RST=?\n$12\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:3") != NULL);
    NEAR(settings.arc_tolerance, 0.1f);
    const char *banner = strstr(engine_output, "GrblHAL 1.1f");
    CHECK(banner != NULL && strstr(banner + 1, "GrblHAL 1.1f") == NULL);
    CHECK(strstr(engine_output, "$12=0.100") != NULL);
    return EXIT_SUCCESS;
}
