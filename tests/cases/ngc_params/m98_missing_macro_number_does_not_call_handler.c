#include "support/macro_parser_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    state_set(STATE_IDLE);
    CHECK(macro_block("M98") == Status_GcodeValueWordMissing);
    CHECK(macro_calls == 0);
    return EXIT_SUCCESS;
}
