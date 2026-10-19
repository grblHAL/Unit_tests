#pragma once
#include "vfs.h"
#include "check.h"
#include <string.h>
static const char *storage_paths[] = {"/flash", "/sd", "/usb", "/ram"};
static vfs_t storage_backends[] = {{.fs_name="flash"}, {.fs_name="sd"}, {.fs_name="usb"}, {.fs_name="ram"}};
static inline void mount_storage_directories(void)
{
    for(unsigned i = 0; i < 4; i++)
        CHECK(vfs_mount(NULL, storage_paths[i], &storage_backends[i], (vfs_st_mode_t){.hidden = i == 3}));
}
static inline void unmount_storage_directories(void)
{
    for(unsigned i = 0; i < 4; i++) CHECK(vfs_unmount(NULL, storage_paths[i]));
}
static inline void check_visible_storage_directories(vfs_dir_t *dir)
{
    unsigned seen = 0, count = 0;
    vfs_dirent_t *entry;
    while((entry = vfs_readdir(dir))) {
        CHECK(entry->st_mode.directory && ++count <= 3);
        unsigned bit = strcmp(entry->name, "flash") == 0 ? 1 :
            (strcmp(entry->name, "sd") == 0 ? 2 : (strcmp(entry->name, "usb") == 0 ? 4 : 0));
        CHECK(bit && !(seen & bit));
        seen |= bit;
    }
    CHECK(seen == 7 && count == 3);
}
