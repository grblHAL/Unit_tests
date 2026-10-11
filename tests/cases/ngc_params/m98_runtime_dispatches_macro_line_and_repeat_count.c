#include "support/macro_parser_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    state_set(STATE_IDLE);
    CHECK(macro_block("N42M98P100L3") == Status_OK);
    CHECK(macro_calls == 1 && called_macro == 100);
    CHECK(macro_line == 42 && macro_repeats == 3);
    CHECK(macro_words.$);
    CHECK(macro_scope == 0);
    return EXIT_SUCCESS;
}
