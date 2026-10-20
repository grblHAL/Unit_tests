#include "support/program_end_host.h"
#include "support/realloc_failure_host.h"
#include "ngc_params.h"
#include "ngc_flowctrl.h"

int main(void)
{
    prepare_program_end(false);
    ngc_flowctrl_init();
    CHECK(program_block("O<guard>IF[1]") == Status_OK);
    CHECK(program_block("#100=7") == Status_OK);
    CHECK(program_block("O<guard>ENDIF") == Status_OK);
    fail_realloc = true;
    CHECK(program_block("O<guard>IF[1]") == Status_OK);
    CHECK(program_block("#100=11") == Status_OK);
    CHECK(program_block("O<guard>ENDIF") == Status_OK);
    fail_realloc = false;
    CHECK(failed_realloc_calls == 0 && !gc_state.skip_blocks);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 11);
    CHECK(plan_get_current_block() == NULL);
    ngc_flowctrl_init();
    return EXIT_SUCCESS;
}
