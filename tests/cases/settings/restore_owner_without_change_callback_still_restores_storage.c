#include "support/restore_owners_host.h"
#include "check.h"

int main(void)
{
    prepare_restore_owners(); driver_owner.on_changed = NULL;
    settings_restore((settings_restore_t){.driver_parameters = true});
    CHECK(driver_owner_restores == 1); CHECK(driver_owner_changes == 0); CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
