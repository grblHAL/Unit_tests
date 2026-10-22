#include "support/program_end_host.h"
#include "support/realloc_failure_host.h"
#include "ngc_params.h"
#include "ngc_flowctrl.h"

int main(void)
{
    prepare_program_end(false);
    ngc_flowctrl_init();
    CHECK(program_block("#100=7") == Status_OK);
    fail_realloc = true;
    CHECK(program_block("O<guard>IF[0]") == Status_FlowControlOutOfMemory);
    fail_realloc = false;
    CHECK(failed_realloc_calls == 1 && !gc_state.skip_blocks);
    CHECK(program_block("#100=9") == Status_OK);
    CHECK(program_block("O<guard>IF[0]") == Status_OK);
    CHECK(program_block("#100=99") == Status_OK);
    CHECK(program_block("O<guard>ELSE") == Status_OK);
    CHECK(program_block("#100=11") == Status_OK);
    CHECK(program_block("O<guard>ENDIF") == Status_OK);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 11);
    CHECK(!gc_state.skip_blocks && plan_get_current_block() == NULL);
    ngc_flowctrl_init();
    return EXIT_SUCCESS;
}
