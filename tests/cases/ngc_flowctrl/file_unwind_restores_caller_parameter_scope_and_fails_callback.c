#include "support/flow_file_host.h"
#include "check.h"
static unsigned callback_calls;
static bool callback_success;
static void finished(uint32_t label, bool success)
{
    CHECK(label == 10);
    callback_calls++;
    callback_success = success;
}
int main(void)
{
    prepare_flow_file();
    CHECK(ngc_param_set(1, 99));
    CHECK(flow_command(10, "SUB") == Status_OK);
    CHECK(ngc_flowctrl_on_endsub_callback(10, finished));
    CHECK(flow_command(10, "ENDSUB") == Status_OK);
    CHECK(flow_command(10, "CALL[12]") == Status_OK);
    CHECK(ngc_call_level() == 1);
    ngc_flowctrl_unwind_stack(hal.stream.file);
    CHECK(ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 99);
    CHECK(callback_calls == 1 && !callback_success);
    CHECK(!ngc_flowctrl_on_endsub_callback(10, finished));
    close_flow_file();
    CHECK(callback_calls == 1);
    return EXIT_SUCCESS;
}
