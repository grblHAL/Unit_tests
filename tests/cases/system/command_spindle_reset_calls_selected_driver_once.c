#include "support/system_command_host.h"
#include "check.h"
static unsigned reset_calls;
static void reset_encoder(void) { reset_calls++; }
int main(void)
{
    prepare_system_command();
    gc_spindle_get(-1)->hal->reset_data = reset_encoder;
    CHECK(system_command("$SR") == Status_OK);
    CHECK(reset_calls == 1);
    return EXIT_SUCCESS;
}
