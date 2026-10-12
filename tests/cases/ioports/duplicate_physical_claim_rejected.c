#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "First claim") != NULL);
    port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "Second claim") == NULL);
    CHECK(port == IOPORT_UNASSIGNED);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    return EXIT_SUCCESS;
}
