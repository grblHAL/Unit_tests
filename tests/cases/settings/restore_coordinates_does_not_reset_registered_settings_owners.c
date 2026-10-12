#include "support/restore_owners_host.h"
#include "check.h"

int main(void)
{
    prepare_restore_owners(); settings_restore((settings_restore_t){.parameters = true});
    CHECK(core_owner_restores == 0 && core_owner_changes == 0);
    CHECK(driver_owner_restores == 0 && driver_owner_changes == 0); CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
