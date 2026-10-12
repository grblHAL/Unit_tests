#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_program = "$I\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "XYZUVW") != NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
