#include "fs_embedded.h"
#include "support/backend_close.h"
#include "check.h"
#include <errno.h>
static const embedded_file_t hidden = {.name = "hidden", .size = 2, .st_mode = {.hidden = true}, .data = {'x','y'}};
static const embedded_file_t *files[] = {&hidden, NULL};

int main(void)
{
    fs_embedded_mount(files);
    vfs_dir_t *dir = vfs_opendir("/embedded/");
    CHECK(dir != NULL);
    CHECK(vfs_readdir(dir) == NULL);
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
    CHECK(vfs_chdir("/embedded") == -1);
    return EXIT_SUCCESS;
}
