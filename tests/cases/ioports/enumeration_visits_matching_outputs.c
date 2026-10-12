#include "support/ioports_host.h"
#include "check.h"
static bool visit_output(xbar_t *pin, uint8_t port, void *context)
{
    CHECK(pin != NULL && pin->cap.output);
    CHECK(port < 2);
    (*(unsigned *)context)++;
    return false;
}

int main(void)
{
    prepare_ioports();
    unsigned visits = 0;
    CHECK(!ioports_enumerate(Port_Digital, Port_Output, (pin_cap_t){.output = true}, visit_output, &visits));
    CHECK(visits == 2);
    return EXIT_SUCCESS;
}
