#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(!ngc_modal_state_restore());
    CHECK(!gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
