#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char imperial[] = "G20"; CHECK(gc_execute_block(imperial) == Status_OK); CHECK(gc_state.modal.units_imperial);
    char metric[] = "G21"; CHECK(gc_execute_block(metric) == Status_OK); CHECK(!gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
