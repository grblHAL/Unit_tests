#include "support/boot_host.h"
#include "support/debug_external_host.h"
int main(void)
{
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(hal.debug.write == NULL);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    debug_writeln("board ready");
    CHECK(strstr(external_output, "board ready" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "board ready") == NULL);
    return EXIT_SUCCESS;
}
