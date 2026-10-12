#pragma once
#include "support/engine_host.h"
#include "vfs.h"
#include "check.h"
#include <string.h>
static unsigned format_calls, mount_calls, unmount_calls, device_mount_calls, device_unmount_calls;
static int format_result;
static bool allow_remount = true;
static inline int format_filesystem(void) { format_calls++; return format_result; }
static inline bool mount_device(const void *device, bool mount) { CHECK(device == (const void *)1); if(mount) device_mount_calls++; else device_unmount_calls++; return !mount || allow_remount; }
static inline void format_mounted(const char *path, const vfs_t *fs, vfs_st_mode_t mode) { (void)fs; (void)mode; CHECK(strcmp(path, "/test/") == 0); mount_calls++; }
static inline void format_unmounted(const char *path) { CHECK(strcmp(path, "/test/") == 0); unmount_calls++; }
static vfs_t format_fs = { .fs_name = "test", .format = format_filesystem, .device_mount = mount_device };
static inline vfs_drive_t *prepare_format_drive(void) { engine_prepare(); CHECK(vfs_mount((const void *)1, "/test", &format_fs, (vfs_st_mode_t){0})); vfs.on_mount = format_mounted; vfs.on_unmount = format_unmounted; return vfs_get_drive("/test"); }
static inline void cleanup_format_drive(void) { vfs.on_unmount = NULL; CHECK(vfs_unmount((const void *)1, "/test")); }
