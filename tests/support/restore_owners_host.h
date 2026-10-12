#pragma once
#include "support/settings_host.h"
static unsigned core_owner_restores, driver_owner_restores;
static unsigned core_owner_changes, driver_owner_changes;
static settings_changed_flags_t core_owner_flags, driver_owner_flags;
static void owner_persistence(void) {}
static void restore_core_owner(void) { core_owner_restores++; }
static void restore_driver_owner(void) { driver_owner_restores++; }
static void core_owner_changed(settings_t *current, settings_changed_flags_t flags)
{ CHECK(current == &settings); CHECK(core_owner_restores == 1); core_owner_changes++; core_owner_flags = flags; }
static void driver_owner_changed(settings_t *current, settings_changed_flags_t flags)
{ CHECK(current == &settings); CHECK(driver_owner_restores == 1); driver_owner_changes++; driver_owner_flags = flags; }
static setting_details_t core_owner = {.is_core = true, .load = owner_persistence,
    .save = owner_persistence, .restore = restore_core_owner, .on_changed = core_owner_changed};
static setting_details_t driver_owner = {.load = owner_persistence,
    .save = owner_persistence, .restore = restore_driver_owner, .on_changed = driver_owner_changed};
static inline void prepare_restore_owners(void)
{
    prepare_settings_store(); CHECK(settings_register(&core_owner)); CHECK(settings_register(&driver_owner));
}
