#include "support/wall_host.h"
#include "check.h"

int main(void)
{
    prepare_wall();
    CHECK(!grbl.home_machine((axes_signals_t){.bits = 7}, (axes_signals_t){0}));
    CHECK(strstr(engine_output, "Homing is not implemented!") != NULL);
    return EXIT_SUCCESS;
}
