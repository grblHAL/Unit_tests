#include "fs_embedded.h"
#include "support/backend_close.h"
#include "check.h"
#include <errno.h>
static const embedded_file_t hidden = {.name = "hidden", .size = 2, .st_mode = {.hidden = true}, .data = {'x','y'}};
static const embedded_file_t *files[] = {&hidden, NULL};
static const embedded_file_t visible = {.name = "visible", .size = 1, .data = {'z'}};
static const embedded_file_t *more[] = {&visible, NULL};

int main(void)
{
    fs_embedded_mount(files);
    CHECK(vfs_chdir("/embedded") == -1);
    fs_embedded_mount(more);
    CHECK(vfs_chdir("/embedded") == 0);
    vfs_dir_t *dir = vfs_opendir("/embedded/");
    CHECK(dir != NULL);
    vfs_dirent_t *entry = vfs_readdir(dir);
    CHECK(entry != NULL && strcmp(entry->name, "visible") == 0);
    CHECK(entry->size == 1);
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
    return EXIT_SUCCESS;
}
