#include "fs_embedded.h"
#include "support/backend_close.h"
#include "check.h"
static const embedded_file_t first = {.name = "first", .size = 3, .data = {'a','b','c'}};
static const embedded_file_t hidden = {.name = "hidden", .size = 2, .st_mode = {.hidden = true}, .data = {'x','y'}};
static const embedded_file_t second = {.name = "second", .size = 1, .data = {'z'}};
static const embedded_file_t *files[] = {&hidden, &first, NULL};
static const embedded_file_t *more[] = {&second, NULL};

int main(void)
{
    fs_embedded_mount(files);
    fs_embedded_mount(more);
    vfs_dir_t *dir = vfs_opendir("/embedded/");
    CHECK(dir != NULL);
    vfs_dirent_t *entry = vfs_readdir(dir);
    CHECK(entry != NULL && strcmp(entry->name, "first") == 0);
    CHECK(entry->size == 3 && !entry->st_mode.hidden);
    entry = vfs_readdir(dir);
    CHECK(entry != NULL && strcmp(entry->name, "second") == 0);
    CHECK(entry->size == 1 && !entry->st_mode.hidden);
    CHECK(vfs_readdir(dir) == NULL);
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
    return EXIT_SUCCESS;
}
