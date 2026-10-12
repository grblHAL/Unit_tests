#include "support/engine_host.h"
#include "canbus.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!canbus_add_filter(0x123, 0x7ff, false, NULL));
    return EXIT_SUCCESS;
}
