#include "support/passthru_host.h"
#include "check.h"

int main(void)
{
    prepare_passthru();
    start_passthru();
    CHECK(pin_values[0]);
    CHECK(!pin_values[1]);
    CHECK(cancelled == 0);
    engine_ticks = 1249;
    engine_execute_tasks(STATE_IDLE);
    CHECK(!pin_values[1]);
    CHECK(cancelled == 0);
    finish_passthru_startup();
    CHECK(pin_values[1]);
    return EXIT_SUCCESS;
}
