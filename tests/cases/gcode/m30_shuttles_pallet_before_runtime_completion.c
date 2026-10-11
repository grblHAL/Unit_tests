#include "support/program_end_host.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);

    CHECK(program_block("M30") == Status_OK);
    CHECK(program_pallet_calls == 1);
    CHECK(program_complete_calls == 1);
    return EXIT_SUCCESS;
}
