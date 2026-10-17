#include "support/flow_static_macro_host.h"
int main(void)
{
    CHECK(NGC_MAX_PARAM_LENGTH == 80);
    char name[NGC_MAX_PARAM_LENGTH + 1];
    memset(name, 'a', sizeof(name) - 1);
    name[sizeof(name) - 1] = 0;
    prepare_static_macro_named(name);
    CHECK(ngc_param_set(1, 99));
    char call[128] = "O<";
    strcat(call, name); strcat(call, ">CALL[12]");
    CHECK(gc_execute_block(call) == Status_OK);
    CHECK(hal.stream.file != NULL && ngc_call_level() == 1);
    vfs_file_t *file = hal.stream.file;
    CHECK(grbl.on_file_end(file, Status_OK) == Status_OK);
    CHECK(hal.stream.file == NULL && ngc_call_level() == 0 && file_closes == 1);
    float value;
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    return EXIT_SUCCESS;
}
