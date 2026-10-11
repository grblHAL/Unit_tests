#include "support/macro_parser_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    state_set(STATE_IDLE);
    CHECK(macro_block("M98P100") == Status_OK);
    CHECK(macro_calls == 1 && macro_repeats == 1);
    return EXIT_SUCCESS;
}
