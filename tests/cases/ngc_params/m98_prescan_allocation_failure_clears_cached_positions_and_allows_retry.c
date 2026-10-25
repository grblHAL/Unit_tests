#include "support/m98_prescan_host.h"
#include "support/calloc_failure_host.h"

int main(void)
{
    prepare_m98_prescan();
    CHECK(ngc_param_set(1, 99));
    vfs_file_t *file = hal.stream.file;
    CHECK(macro_block("M98P10") == Status_OK);
    file_position = 4;
    CHECK(macro_block("O10") == Status_OK);
    CHECK(gc_macro_get_pos(10, file) == 4);
    fail_calloc = true;
    status_code_t status = macro_block("M98P20");
    fail_calloc = false;
    CHECK(status == Status_FlowControlOutOfMemory && failed_calloc_calls == 1);
    CHECK(hal.stream.file == file && file_closes == 0);
    CHECK(gc_macro_get_pos(10, file) == 0 && gc_macro_get_pos(20, file) == 0);
    CHECK(macro_calls == 0 && ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    CHECK(macro_block("M98P10") == Status_OK);
    CHECK(macro_block("M98P20") == Status_OK);
    file_position = 1;
    CHECK(macro_block("O10") == Status_OK);
    file_position = 8;
    CHECK(macro_block("O20") == Status_OK);
    CHECK(gc_macro_get_pos(10, file) == 1 && gc_macro_get_pos(20, file) == 8);
    CHECK(macro_calls == 0 && failed_calloc_calls == 1);
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    gc_init(false);
    CHECK(gc_macro_get_pos(10, file) == 0 && gc_macro_get_pos(20, file) == 0);
    close_flow_file();
    return EXIT_SUCCESS;
}
