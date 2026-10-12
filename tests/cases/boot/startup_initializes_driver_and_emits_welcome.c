#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(strstr(engine_output, "GrblHAL 1.1f") != NULL);
    CHECK(sys.driver_started);
    return EXIT_SUCCESS;
}
