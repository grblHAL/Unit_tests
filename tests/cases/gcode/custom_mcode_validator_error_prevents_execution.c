#include "support/user_mcode_host.h"
#include "check.h"

int main(void)
{
    prepare_user_mcodes();
    user_validation_result = Status_GcodeValueOutOfRange;
    CHECK(user_mcode_block("G20M400") == Status_GcodeValueOutOfRange);
    CHECK(user_validate_calls == 1 && user_execute_calls == 0);
    CHECK(!gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
