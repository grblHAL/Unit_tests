#pragma once
#include "fatfs_host.h"
#include "sdcard.h"
#include "grbl/task.h"
extern grbl_t grbl;
extern settings_t settings;
extern system_t sys;
extern bool sd_detectable, sd_present;
extern unsigned sd_messages, sd_plugins, sd_options, sd_setups, sd_changes, sd_custom_mounts,
    sd_custom_unmounts;
extern char sd_output[256];
extern sdcard_events_t *sd_events;
void sd_prepare(void);
void sd_startup(void);
void sd_run(void);
status_code_t sd_command(const char *name);
void sd_report(bool all);
void sd_custom_events(void);
