#include "support/engine_host.h"
#include "canbus.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!canbus_enabled());
    return EXIT_SUCCESS;
}
