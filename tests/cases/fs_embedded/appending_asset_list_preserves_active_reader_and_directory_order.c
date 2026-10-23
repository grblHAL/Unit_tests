#include "fs_embedded.h"
#include "support/mount_result_host.h"
#include <string.h>
static const embedded_file_t first = {.name = "first", .size = 5, .data = {'a','b','c','d','e'}};
static const embedded_file_t *files[] = {&first, NULL};
static const embedded_file_t later = {.name = "later", .size = 1, .data = {'z'}};
static const embedded_file_t *more[] = {&later, NULL};
static const embedded_file_t last = {.name = "last", .size = 1, .data = {'q'}};
static const embedded_file_t *final_files[] = {&last, NULL};
int main(void)
{
    CHECK_MOUNT_RESULT(fs_embedded_mount(files), true);
    vfs_file_t *file = vfs_open("/embedded/first", "r");
    CHECK(file != NULL);
    char data[6] = {0};
    CHECK(vfs_read(data, 1, 2, file) == 2 && memcmp(data, "ab", 2) == 0);
    CHECK_MOUNT_RESULT(fs_embedded_mount(more), true);
    CHECK_MOUNT_RESULT(fs_embedded_mount(final_files), true);
    vfs_dir_t *dir = vfs_opendir("/embedded");
    CHECK(dir != NULL);
    vfs_dirent_t *entry = vfs_readdir(dir);
    CHECK(entry != NULL && strcmp(entry->name, "first") == 0);
    entry = vfs_readdir(dir);
    CHECK(entry != NULL && strcmp(entry->name, "later") == 0);
    entry = vfs_readdir(dir);
    CHECK(entry != NULL && strcmp(entry->name, "last") == 0);
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
    CHECK(vfs_tell(file) == 2);
    CHECK(vfs_read(data, 1, 3, file) == 3 && memcmp(data, "cde", 3) == 0);
    vfs_close(file);
    return EXIT_SUCCESS;
}
