#include "support/ioports_host.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_can_claim_explicit());
    hal.port.claim = NULL;
    CHECK(!ioport_can_claim_explicit());
    hal.port.get_pin_info = NULL;
    CHECK(!ioport_can_claim_explicit());
    return EXIT_SUCCESS;
}
