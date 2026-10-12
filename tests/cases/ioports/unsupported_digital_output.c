#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!ioport_digital_out(2, 1));
    return EXIT_SUCCESS;
}
