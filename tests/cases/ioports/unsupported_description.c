#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!ioport_set_description(Port_Digital, Port_Output, 2, "Output"));
    return EXIT_SUCCESS;
}
