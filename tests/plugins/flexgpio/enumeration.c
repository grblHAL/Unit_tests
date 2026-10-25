#include "flex_host.h"
static unsigned seen;
static bool low_level;
static void visit(xbar_t *pin, void *data)
{
    CHECK(data == &seen);
    if (pin->cap.external)
    {
        CHECK(pin->group == PinGroup_AuxInput || pin->group == PinGroup_AuxOutput);
        CHECK(pin->port);
        if (!low_level)
            CHECK(strcmp(pin->port, "FLEXGPIO:") == 0);
        seen++;
    }
}
int main(void)
{
    flex_start();
    hal.enumerate_pins(false, visit, &seen);
    CHECK(seen == 20);
    low_level = true;
    hal.enumerate_pins(true, visit, &seen);
    CHECK(seen == 40);
    hal.driver_reset();
    unsigned before = chains;
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(chains == before + 3);
    return 0;
}
