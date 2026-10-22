#include "support/ganging_host.h"
static unsigned normal_queries, square_queries;
static axes_signals_t driver_axes(bool auto_squared)
{
    if(auto_squared) square_queries++; else normal_queries++;
    return (axes_signals_t){.mask = X_AXIS_BIT};
}
int main(void)
{
    ganging_driver_axes = driver_axes;
    prepare_ganging();
    unsigned normal_before = normal_queries, square_before = square_queries;
    CHECK(hal.stepper.get_ganged(false).mask == (X_AXIS_BIT | Y_AXIS_BIT));
    CHECK(hal.stepper.get_ganged(true).mask == (X_AXIS_BIT | Y_AXIS_BIT));
    CHECK(normal_queries == normal_before + 1 && square_queries == square_before + 1);
    return EXIT_SUCCESS;
}
