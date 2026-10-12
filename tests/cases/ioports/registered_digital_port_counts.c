#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioports_available(Port_Digital, Port_Input) == 2);
    CHECK(ioports_available(Port_Digital, Port_Output) == 2);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 2);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
