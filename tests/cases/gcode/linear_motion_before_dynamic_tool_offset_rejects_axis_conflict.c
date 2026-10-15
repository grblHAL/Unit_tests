#include "support/parser_rejection_host.h"
int main(void)
{
    prepare_parser_rejection();
    char block[] = "G1G43.1Z100F100";
    CHECK(gc_execute_block(block) == Status_GcodeAxisCommandConflict);
    check_rejection_preserved_coordinates();
    return EXIT_SUCCESS;
}
