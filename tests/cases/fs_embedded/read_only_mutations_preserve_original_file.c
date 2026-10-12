#include "fs_embedded.h"
#include "support/backend_close.h"
#include "check.h"
#include <errno.h>
static const embedded_file_t job = {.name = "job", .size = 2, .data = {'o','k'}};
static const embedded_file_t *files[] = {&job, NULL};

int main(void)
{
    fs_embedded_mount(files);
    CHECK(vfs_unlink("/embedded/job") == -1);
    CHECK(vfs_errno == EROFS);
    CHECK(vfs_mkdir("/embedded/subdir") == -1);
    CHECK(vfs_errno == EROFS);
    CHECK(vfs_rmdir("/embedded/subdir") == -1);
    CHECK(vfs_errno == EROFS);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/embedded/job", &st) == 0 && st.st_size == 2);
    vfs_file_t *file = vfs_open("/embedded/job", "r");
    CHECK(file != NULL);
    char data[3] = {0};
    CHECK(vfs_read(data, 1, 2, file) == 2);
    CHECK(strcmp(data, "ok") == 0);
    backend_close(file);
    return EXIT_SUCCESS;
}
