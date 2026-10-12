#include "support/restore_owners_host.h"
#include "check.h"

int main(void)
{
    prepare_restore_owners(); settings_restore((settings_restore_t){.defaults = true, .driver_parameters = true});
    CHECK(core_owner_restores == 1 && core_owner_changes == 1);
    CHECK(driver_owner_restores == 1 && driver_owner_changes == 1);
    CHECK(core_owner_flags.restore_defaults); CHECK(driver_owner_flags.value == 0); CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
