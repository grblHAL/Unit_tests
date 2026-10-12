#include "support/restore_owners_host.h"
#include "check.h"

int main(void)
{
    prepare_restore_owners(); settings_restore((settings_restore_t){.driver_parameters = true});
    CHECK(driver_owner_restores == 1 && driver_owner_changes == 1); CHECK(driver_owner_flags.value == 0);
    CHECK(core_owner_restores == 0 && core_owner_changes == 0); CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
