#include "support/flow_file_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_file();
    file_position = 2;
    CHECK(flow_command(10, "REPEAT[2]") == Status_OK);
    file_position = 8;
    CHECK(flow_command(10, "CONTINUE") == Status_OK);
    CHECK(file_position == 2);
    CHECK(!flow_skip);
    file_position = 8;
    CHECK(flow_command(10, "CONTINUE") == Status_OK);
    CHECK(flow_skip);
    CHECK(file_position == 8);
    CHECK(flow_command(10, "ENDREPEAT") == Status_OK);
    CHECK(!flow_skip);
    close_flow_file();
    return EXIT_SUCCESS;
}
