#include "support/flow_named_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_named_macro();
    CHECK(ngc_param_set(1, 99));
    char name[] = "missing";
    ngc_string_id_t label = ngc_string_param_set_name(name);
    CHECK(flow_command(label, "CALL[12]") == Status_FileOpenFailed);
    CHECK(hal.stream.file == NULL);
    CHECK(hal.stream.read == stream_get_null);
    CHECK(ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 99);
    return EXIT_SUCCESS;
}
