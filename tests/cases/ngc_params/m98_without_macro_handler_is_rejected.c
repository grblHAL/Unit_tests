#include "support/macro_parser_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    grbl.on_macro_execute = NULL;
    CHECK(macro_block("M98P100") == Status_GcodeUnsupportedCommand);
    CHECK(macro_calls == 0);
    return EXIT_SUCCESS;
}
