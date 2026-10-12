#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_set_description(Port_Digital, Port_Output, 0, "Fixture output"));
    CHECK(ioport_find_free(Port_Digital, Port_Output, (pin_cap_t){0}, "Fixture output") == 0);
    CHECK(ioport_find_free(Port_Digital, Port_Output, (pin_cap_t){0}, "Missing output") == IOPORT_UNASSIGNED);
    return EXIT_SUCCESS;
}
