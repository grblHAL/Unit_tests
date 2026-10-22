#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_set_description(Port_Digital, Port_Output, 0, "Fixture output"));
    CHECK(ioport_find_free(Port_Digital, Port_Output, (pin_cap_t){0}, "Fixture output") == 0);
    CHECK(ioport_find_free(Port_Digital, Port_Output, (pin_cap_t){0}, "Missing output") == IOPORT_UNASSIGNED);
    CHECK(ioport_find_free(Port_Digital, Port_Output, (pin_cap_t){.claimable = true}, "0") == 0);
    CHECK(ioport_find_free(Port_Digital, Port_Output, (pin_cap_t){.claimable = true}, "1") == 1);
    CHECK(ioport_find_free(Port_Digital, Port_Output, (pin_cap_t){.claimable = true}, "") == 1);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    CHECK(!digital_pins[Port_Output][0].mode.claimed);
    CHECK(!digital_pins[Port_Output][1].mode.claimed);
    CHECK(strcmp(digital_pins[Port_Output][0].description, "Fixture output") == 0);
    return EXIT_SUCCESS;
}
