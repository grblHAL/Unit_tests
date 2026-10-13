#pragma once
#include "fs_embedded.h"
#include "vfs.h"
#include "check.h"
#include <errno.h>
#include <string.h>

static const embedded_file_t seek_fixture = {
    .name = "seek.txt", .size = 5, .data = {'h', 'e', 'l', 'l', 'o'}
};
static const embedded_file_t *seek_files[] = {&seek_fixture, NULL};
static inline vfs_file_t *open_seek_fixture(void)
{
    fs_embedded_mount(seek_files);
    vfs_file_t *file = vfs_open("/embedded/seek.txt", "r");
    CHECK(file != NULL);
    return file;
}
