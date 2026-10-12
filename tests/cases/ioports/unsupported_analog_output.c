#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!ioport_analog_out(2, 1.25f));
    return EXIT_SUCCESS;
}
