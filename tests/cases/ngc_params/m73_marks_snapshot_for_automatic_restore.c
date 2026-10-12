#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("M73") == Status_OK);
    CHECK(ngc_modal_state_get() != NULL);
    CHECK(ngc_modal_state_get()->modal.auto_restore);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
