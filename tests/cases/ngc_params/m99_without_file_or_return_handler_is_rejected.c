#include "support/macro_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    grbl.on_macro_return = NULL;
    CHECK(hal.stream.file == NULL);
    CHECK(macro_block("M99") == Status_GcodeUnsupportedCommand);
    return EXIT_SUCCESS;
}
