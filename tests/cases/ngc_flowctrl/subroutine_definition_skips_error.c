#include "support/flow_file_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_file();
    CHECK(flow_command(10, "SUB") == Status_OK);
    CHECK(flow_skip);
    CHECK(flow_command(10, "ERROR[5]") == Status_OK);
    CHECK(flow_skip);
    CHECK(flow_command(10, "ENDSUB") == Status_OK);
    CHECK(!flow_skip);
    close_flow_file();
    return EXIT_SUCCESS;
}
