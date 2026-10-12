#include "support/flow_host.h"
#include "check.h"

int main(void)
{
    prepare_flow();
    CHECK(flow_command(10, "IF[1]") == Status_OK);
    CHECK(flow_command(10, "ERROR[0]") == Status_OK);
    CHECK(flow_command(10, "ENDIF") == Status_OK);
    return EXIT_SUCCESS;
}
