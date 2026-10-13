#include "support/ngc_tool_change_host.h"
#include "support/named_parameter_host.h"

int main(void)
{
    vfs_file_t *file = prepare_ngc_change_file();
    NEAR(read_named_parameter("_current_tool"), 0);
    NEAR(read_named_parameter("_current_pocket"), 0);
    NEAR(read_named_parameter("_selected_tool"), -1);
    NEAR(read_named_parameter("_selected_pocket"), -1);
    CHECK(named_parameter_block("T2") == Status_OK);
    NEAR(read_named_parameter("_selected_tool"), 2);
    NEAR(read_named_parameter("_selected_pocket"), 2);
    NEAR(read_named_parameter("_current_tool"), 0);
    CHECK(named_parameter_block("M61Q2") == Status_OK);
    NEAR(read_named_parameter("_current_tool"), 2);
    NEAR(read_named_parameter("_current_pocket"), 2);
    NEAR(read_named_parameter("_selected_tool"), -1);
    NEAR(read_named_parameter("_selected_pocket"), -1);
    stream_redirect_close(file);
    CHECK(file_closes == 1);
    return EXIT_SUCCESS;
}
