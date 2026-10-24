#pragma once
#include "hal.h"
#include "fs_ram.h"
#include "vfs.h"
#include "check.h"
#include <string.h>
static inline void check_ram_shrink_prefix(bool committed)
{
    fs_ram_mount();
    vfs_file_t *file = vfs_open("/ram/job", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("G1X1\nG1X2\n", 1, 10, file) == 10);
    if(committed) {
        vfs_close(file);
        file = vfs_open("/ram/job", "r");
        CHECK(file != NULL);
    }
    CHECK(vfs_truncate(file, 5) == 0);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/job", &st) == 0 && st.st_size == 5);
    if(!committed) {
        vfs_close(file);
        file = vfs_open("/ram/job", "r");
        CHECK(file != NULL);
    }
    CHECK(vfs_seek(file, 0) == 0);
    char prefix[6] = {0};
    CHECK(vfs_read(prefix, 1, 5, file) == 5);
    CHECK(memcmp(prefix, "G1X1\n", 5) == 0);
    CHECK(vfs_eof(file));
    vfs_close(file);
    CHECK(vfs_open("/ram/job", "r") == NULL);
}
