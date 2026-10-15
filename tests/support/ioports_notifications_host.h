#pragma once
#include "support/ioports_settings_host.h"

static unsigned io_notification_calls, io_loaded_calls;
static setting_id_t io_notified_setting;
static void io_setting_notification(setting_id_t id)
{
    if(id == Settings_IoPort_InvertIn) CHECK(input_config_calls[1] > 0);
    if(id == Settings_IoPort_InvertOut) CHECK(output_config_calls[0] > 0);
    io_notified_setting = id;
    io_notification_calls++;
}
static void io_loaded_notification(void)
{
    CHECK(input_config_calls[0] && input_config_calls[1]);
    CHECK(output_config_calls[0] && output_config_calls[1]);
    io_loaded_calls++;
}
static inline void prepare_io_notifications(void)
{
    prepare_io_settings();
    ioports_add_settings(io_loaded_notification, io_setting_notification);
}
