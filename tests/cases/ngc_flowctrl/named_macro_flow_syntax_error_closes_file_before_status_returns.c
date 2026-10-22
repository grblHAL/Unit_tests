#include "support/flow_named_macro_host.h"
int main(void)
{
    prepare_named_macro();
    CHECK(ngc_param_set(1, 99));
    CHECK(flow_command(named_macro_label, "CALL[12]") == Status_OK);
    vfs_file_t *file = hal.stream.file;
    CHECK(file != NULL && ngc_call_level() == 1);
    ngc_string_id_t wrong_label = ngc_string_param_set_name("wrong_header");
    CHECK(wrong_label > NGC_MAX_PARAM_ID && wrong_label != named_macro_label);
    status_code_t status = flow_command(wrong_label, "SUB");
    CHECK(status == Status_FlowControlSyntaxError);
    CHECK(grbl.report.status_message(status) == status);
    bool closed_on_error = hal.stream.file == NULL && hal.stream.read == stream_get_null;
    /* Release the observed orphan before the regression assertion. */
    if(hal.stream.file == file) stream_redirect_close(file);
    ngc_string_param_delete(wrong_label);
    CHECK(ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    CHECK(closed_on_error);
    return EXIT_SUCCESS;
}
