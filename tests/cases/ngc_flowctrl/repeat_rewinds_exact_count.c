#include "support/flow_file_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_file();
    file_position = 2;
    CHECK(flow_command(10, "REPEAT[3]") == Status_OK);
    CHECK(!flow_skip);
    for(unsigned iteration = 0; iteration < 3; iteration++) {
        file_position = 8;
        CHECK(flow_command(10, "ENDREPEAT") == Status_OK);
        CHECK(file_position == (iteration < 2 ? 2 : 8));
    }
    CHECK(!flow_skip);
    CHECK(flow_command(10, "ENDREPEAT") == Status_FlowControlSyntaxError);
    close_flow_file();
    return EXIT_SUCCESS;
}
