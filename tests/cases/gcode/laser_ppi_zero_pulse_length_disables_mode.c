#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    (void)gc_laser_ppi_enable(1000, 50);
    CHECK(gc_state.is_laser_ppi_mode);
    CHECK(!gc_laser_ppi_enable(1000, 0));
    CHECK(!gc_state.is_laser_ppi_mode);
    return EXIT_SUCCESS;
}
