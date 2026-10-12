#pragma once
#include "support/settings_host.h"
static uint32_t registry_value;
static setting_detail_t registry_setting[] = {
    {.id=(setting_id_t)1001, .group=(setting_group_t)1000, .name="Channel calibration",
     .type=Setting_NonCore, .datatype=Format_Integer, .value=&registry_value,
     .flags={.increment=2}}
};
static setting_descr_t registry_descriptions[] = {
    {.id=(setting_id_t)1001, .description="Channel ? calibration"}
};
static const setting_group_detail_t registry_groups[] = {
    {.id=(setting_group_t)1000, .parent=Group_General, .name="Channels"}
};
static void registry_persistence(void) {}
static setting_id_t registry_normalize(setting_id_t id)
{
    return id >= (setting_id_t)1001 && id <= (setting_id_t)1019 ? (setting_id_t)1001 : (setting_id_t)0;
}
static setting_details_t registry_details = {
    .n_settings=1, .settings=registry_setting,
    .n_descriptions=1, .descriptions=registry_descriptions,
    .n_groups=1, .groups=registry_groups,
    .load=registry_persistence, .restore=registry_persistence, .save=registry_persistence,
    .normalize=registry_normalize
};
static inline void prepare_settings_registry(void)
{
    prepare_settings_store();
    CHECK(settings_register(&registry_details));
}
