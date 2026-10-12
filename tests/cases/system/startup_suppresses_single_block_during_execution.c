#include "support/system_command_host.h"
#include "nvs.h"
#include "check.h"
static stream_write_ptr startup_write;
static unsigned observed_writes;
static void observe_startup(const char *text)
{
    CHECK(!sys.flags.single_block);
    observed_writes++;
    startup_write(text);
}
int main(void)
{
    prepare_system_command();
    startup_write = hal.stream.write;
    hal.stream.write = observe_startup;
    stored_line_t first = "G20|G91", second = "G21";
    settings_write_startup_line(0, first);
    settings_write_startup_line(1, second);
    sys.flags.single_block = true;
    system_execute_startup(NULL);
    CHECK(observed_writes > 0);
    CHECK(sys.flags.single_block);
    CHECK(!(sys.rt_exec_state & EXEC_FEED_HOLD));
    return EXIT_SUCCESS;
}
