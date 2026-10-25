#include "bltouch_host.h"
int main(void)
{
    load_bltouch();
    CHECK(system_bltouch("BLTEST") == Status_OK && angle == 120 && delayed_task &&
          delayed_ms == 12000);
    command_bltouch(Probe_Stow);
    CHECK(angle == 90 && delayed_task == NULL);
    CHECK(system_bltouch("BLRESET") == Status_OK && angle == 160 && delayed_task &&
          delayed_ms == 10);
    NEAR(last_delay, 0.5f);
    run_bltouch_delayed();
    CHECK(angle == 90 && delayed_task == NULL);
    NEAR(last_delay, 0.75f);
    return 0;
}
