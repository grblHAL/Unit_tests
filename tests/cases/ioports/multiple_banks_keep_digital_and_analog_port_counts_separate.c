#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(ioports_available(Port_Digital, Port_Input) == 5);
    CHECK(ioports_available(Port_Digital, Port_Output) == 5);
    CHECK(ioports_available(Port_Analog, Port_Input) == 4);
    CHECK(ioports_available(Port_Analog, Port_Output) == 4);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 5);
    CHECK(ioports_unclaimed(Port_Analog, Port_Output) == 4);
    return EXIT_SUCCESS;
}
