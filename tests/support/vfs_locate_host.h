#pragma once
#include "vfs.h"
#include "check.h"
#include <string.h>
static bool root_found, little_found, embedded_found;
static unsigned lookup_count;
static char lookup_trace[256];
static int locate_stat(const char *backend, bool found, const char *path, vfs_stat_t *st)
{
    CHECK(strlen(lookup_trace) + strlen(backend) + strlen(path) + 3 < sizeof(lookup_trace));
    strcat(lookup_trace, backend); strcat(lookup_trace, ":"); strcat(lookup_trace, path); strcat(lookup_trace, ";");
    lookup_count++; memset(st, 0, sizeof(*st)); st->st_size = 42;
    return found ? 0 : -1;
}
static int root_stat(const char *path, vfs_stat_t *st) { return locate_stat("root",root_found,path,st); }
static int little_stat(const char *path, vfs_stat_t *st) { return locate_stat("little",little_found,path,st); }
static int embedded_stat(const char *path, vfs_stat_t *st) { return locate_stat("embedded",embedded_found,path,st); }
static const vfs_t locate_root = {.fs_name = "root", .fstat = root_stat};
static const vfs_t locate_little = {.fs_name = "littlefs", .fstat = little_stat};
static const vfs_t locate_embedded = {.fs_name = "embedded", .fstat = embedded_stat};
static inline void mount_lookup_sources(bool root, bool little, bool embedded)
{
    if(root) CHECK(vfs_mount(NULL,"/",&locate_root,(vfs_st_mode_t){0}));
    if(little) CHECK(vfs_mount(NULL,"/littlefs",&locate_little,(vfs_st_mode_t){0}));
    if(embedded) CHECK(vfs_mount(NULL,"/embedded",&locate_embedded,(vfs_st_mode_t){0}));
}
static inline void unmount_lookup_sources(bool root, bool little, bool embedded)
{
    if(embedded) CHECK(vfs_unmount(NULL,"/embedded"));
    if(little) CHECK(vfs_unmount(NULL,"/littlefs"));
    if(root) CHECK(vfs_unmount(NULL,"/"));
}
