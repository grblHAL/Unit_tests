#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    uint8_t port = 0;
    xbar_t *claimed = ioport_claim(Port_Digital, Port_Output, &port, "Fixture output");
    CHECK(claimed != NULL);
    CHECK(claimed->id == 0);
    CHECK(claimed->mode.claimed);
    CHECK(strcmp(claimed->description, "Fixture output") == 0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 2);
    return EXIT_SUCCESS;
}
