#include "support/flow_file_host.h"
#include "check.h"
static unsigned sub_callbacks;
static bool sub_success;
static void sub_finished(uint32_t label, bool success)
{
    CHECK(label == 10);
    sub_callbacks++;
    sub_success = success;
}

int main(void)
{
    prepare_flow_file();
    CHECK(ngc_param_set(1, 99));
    file_position = 2;
    CHECK(flow_command(10, "SUB") == Status_OK);
    CHECK(flow_skip);
    CHECK(ngc_flowctrl_on_endsub_callback(10, sub_finished));
    CHECK(flow_command(10, "ENDSUB") == Status_OK);
    CHECK(!flow_skip);
    file_position = 9;
    CHECK(flow_command(10, "CALL[12]") == Status_OK);
    CHECK(file_position == 2);
    CHECK(ngc_call_level() == 1);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 12);
    file_position = 8;
    CHECK(flow_command(10, "RETURN[7]") == Status_OK);
    CHECK(file_position == 9);
    CHECK(ngc_call_level() == 0);
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 99);
    char result[] = "_value";
    CHECK(ngc_named_param_get(result, &value));
    NEAR(value, 7);
    CHECK(sub_callbacks == 1);
    CHECK(sub_success);
    close_flow_file();
    return EXIT_SUCCESS;
}
