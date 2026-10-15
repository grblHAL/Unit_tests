#include "support/flow_static_macro_host.h"
int main(void)
{
    prepare_static_macro();
    CHECK(ngc_param_set(1, 99));
    stream_read_ptr previous_read = hal.stream.read;
    char call[] = "O<missing_workholding_fixture_setup_macro_with_a_long_filename>CALL[12]";
    CHECK(gc_execute_block(call) == Status_FileOpenFailed);
    CHECK(hal.stream.file == NULL && hal.stream.read == previous_read);
    CHECK(ngc_call_level() == 0 && file_closes == 0);
    float value;
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    return EXIT_SUCCESS;
}
