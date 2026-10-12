#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_program = "$SLP\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(state_get() == STATE_IDLE);
    char expected[32];
    snprintf(expected, sizeof(expected), "error:%u", (unsigned)Status_InvalidStatement);
    CHECK(strstr(engine_output, expected) != NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    CHECK(strstr(engine_output, "Sleeping") == NULL);
    return EXIT_SUCCESS;
}
