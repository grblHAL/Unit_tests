#include "support/ioports_host.h"

static bool find_output(xbar_t *pin, uint8_t port, void *context)
{
    CHECK(pin == &digital_pins[Port_Output][0]);
    CHECK(port == 0);
    (*(unsigned *)context)++;
    return true;
}

int main(void)
{
    prepare_ioports();
    unsigned visits = 0;
    CHECK(ioports_enumerate(Port_Digital, Port_Output, (pin_cap_t){0}, find_output, &visits));
    CHECK(visits == 1);
    return EXIT_SUCCESS;
}
