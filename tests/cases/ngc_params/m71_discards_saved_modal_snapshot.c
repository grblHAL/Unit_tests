#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("M70") == Status_OK);
    CHECK(ngc_modal_state_get() != NULL);
    CHECK(program_block("M71") == Status_OK);
    CHECK(ngc_modal_state_get() == NULL);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
