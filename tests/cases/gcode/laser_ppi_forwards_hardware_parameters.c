#include "support/engine_host.h"
#include "check.h"
static unsigned ppi_calls;
static uint_fast16_t captured_ppi, captured_length;
static bool capture_ppi(uint_fast16_t ppi, uint_fast16_t length)
{
    ppi_calls++;
    captured_ppi = ppi;
    captured_length = length;
    return true;
}

int main(void)
{
    engine_parser_prepare();
    grbl.on_laser_ppi_enable = capture_ppi;
    CHECK(gc_laser_ppi_enable(1200, 75));
    CHECK(gc_state.is_laser_ppi_mode);
    CHECK(ppi_calls == 1);
    CHECK(captured_ppi == 1200 && captured_length == 75);
    CHECK(gc_laser_ppi_enable(0, 0));
    CHECK(!gc_state.is_laser_ppi_mode);
    CHECK(ppi_calls == 2);
    CHECK(captured_ppi == 0 && captured_length == 0);
    return EXIT_SUCCESS;
}
