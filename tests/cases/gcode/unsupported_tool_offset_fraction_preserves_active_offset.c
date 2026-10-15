#include "support/parser_rejection_host.h"
int main(void)
{
    prepare_parser_rejection();
    char block[] = "G20G43.3Z100";
    CHECK(gc_execute_block(block) == Status_GcodeUnsupportedCommand);
    check_rejection_preserved_coordinates();
    return EXIT_SUCCESS;
}
