#pragma once
#include "support/settings_host.h"
static char element_format[64];
static uint32_t element_value;
static const setting_detail_t element_setting[] = {
    {.id=(setting_id_t)1001, .name="Mode options", .type=Setting_NonCore,
     .datatype=Format_Bitfield, .format=element_format, .value=&element_value}
};
static void element_persistence(void) {}
static setting_details_t element_details = {
    .n_settings=1, .settings=element_setting,
    .load=element_persistence, .restore=element_persistence, .save=element_persistence
};
static inline void prepare_setting_elements(const char *format)
{
    prepare_settings_store();
    CHECK(strlen(format) < sizeof(element_format));
    strcpy(element_format, format);
    CHECK(settings_register(&element_details));
}
