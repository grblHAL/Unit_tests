#include "support/restore_owners_host.h"
#include "check.h"
static unsigned optional_changes; static settings_changed_flags_t optional_flags;
static void capture_optional_change(settings_t *current, settings_changed_flags_t flags)
{ CHECK(current == &settings); optional_changes++; optional_flags = flags; }
int main(void)
{
    core_owner.restore = NULL; core_owner.on_changed = capture_optional_change;
    prepare_restore_owners(); settings_restore((settings_restore_t){.defaults = true});
    CHECK(core_owner_restores == 0); CHECK(optional_changes == 1); CHECK(optional_flags.restore_defaults);
    CHECK(driver_owner_restores == 0 && driver_owner_changes == 0);
    return EXIT_SUCCESS;
}
