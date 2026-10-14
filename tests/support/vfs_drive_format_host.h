#pragma once
#include "support/engine_host.h"
#include "vfs.h"
#include "check.h"
#include <string.h>
static int format_result;
static bool format_remount_ok = true, drive_space_ok = true;
static unsigned format_calls, format_mount_calls, format_drain_calls, drive_space_calls;
static char format_events[32];
static int format_device;
static vfs_t format_fs;
static void format_event(char code)
{ size_t n = strlen(format_events); CHECK(n + 1 < sizeof(format_events)); format_events[n] = code; format_events[n+1] = 0; }
static uint16_t format_tx_count(void) { format_drain_calls++; format_event('T'); return 0; }
static int format_backend(void) { format_calls++; format_event('F'); return format_result; }
static bool format_mount_device(const void *device, bool mount)
{
    CHECK(device == &format_device); format_mount_calls++; format_event(mount ? 'R' : 'D');
    return !mount || format_remount_ok;
}
static void format_unmounted(const char *path) { CHECK(strcmp(path,"/store/") == 0); format_event('U'); }
static void format_mounted(const char *path, const vfs_t *fs, vfs_st_mode_t mode)
{ CHECK(strcmp(path,"/store/") == 0); CHECK(fs == &format_fs); CHECK(mode.directory); format_event('M'); }
static bool format_getfree(vfs_free_t *space)
{ drive_space_calls++; space->size = 8192; space->used = 512; return drive_space_ok; }
static inline vfs_drive_t *prepare_format_drive(void)
{
    engine_prepare(); hal.stream.get_tx_buffer_count = format_tx_count;
    format_fs = (vfs_t){.fs_name="store",.format=format_backend,.device_mount=format_mount_device,.fgetfree=format_getfree};
    CHECK(vfs_mount(&format_device,"/store",&format_fs,(vfs_st_mode_t){.directory=true}));
    vfs.on_unmount = format_unmounted; vfs.on_mount = format_mounted;
    return vfs_get_drive("/store/file.nc");
}
static inline void cleanup_format_drive(void)
{
    vfs.on_unmount = NULL; vfs.on_mount = NULL;
    CHECK(vfs_unmount(&format_device,"/store"));
}
