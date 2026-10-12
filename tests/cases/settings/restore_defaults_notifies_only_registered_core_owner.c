#include "support/restore_owners_host.h"
#include "check.h"

int main(void)
{
    prepare_restore_owners(); settings_restore((settings_restore_t){.defaults = true});
    CHECK(core_owner_restores == 1 && core_owner_changes == 1);
    CHECK(core_owner_flags.restore_defaults && core_owner_flags.spindle);
    CHECK(driver_owner_restores == 0 && driver_owner_changes == 0);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
