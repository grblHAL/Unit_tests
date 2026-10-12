#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    CHECK(strstr(engine_output, "ok") != NULL);
    CHECK(boot_reads == 3);
    return EXIT_SUCCESS;
}
