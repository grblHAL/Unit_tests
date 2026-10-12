#include "support/flow_file_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_file();
    CHECK(ngc_param_set(100, 1));
    file_position = 2;
    CHECK(flow_command(10, "WHILE[#100]") == Status_OK);
    CHECK(!flow_skip);
    file_position = 8;
    CHECK(flow_command(10, "ENDWHILE") == Status_OK);
    CHECK(file_position == 2);
    CHECK(ngc_param_set(100, 0));
    file_position = 8;
    CHECK(flow_command(10, "ENDWHILE") == Status_OK);
    CHECK(file_position == 8);
    CHECK(!flow_skip);
    close_flow_file();
    return EXIT_SUCCESS;
}
