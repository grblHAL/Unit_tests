#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_claimable(Port_Digital, Port_Input, IOPORT_UNASSIGNED));
    CHECK(ioport_claimable(Port_Digital, Port_Output, IOPORT_UNASSIGNED));
    return EXIT_SUCCESS;
}
