#include "support/boot_host.h"
int main(void)
{
    boot_program = "$12=0.1\n$C\n$RST=$\n$12\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:8") != NULL);
    NEAR(settings.arc_tolerance, 0.1f);
    CHECK(strstr(engine_output, "$12=0.100") != NULL);
    return EXIT_SUCCESS;
}
