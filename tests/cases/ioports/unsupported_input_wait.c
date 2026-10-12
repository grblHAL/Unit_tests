#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(ioport_wait_on_input(Port_Digital, 2, WaitMode_Immediate, 0) == -1);
    return EXIT_SUCCESS;
}
