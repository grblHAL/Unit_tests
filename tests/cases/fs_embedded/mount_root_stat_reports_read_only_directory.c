#include "fs_embedded.h"
#include "check.h"
static const embedded_file_t first = {.name = "first", .size = 1, .data = {'a'}};
static const embedded_file_t *files[] = {&first, NULL};
int main(void)
{
    fs_embedded_mount(files);
    vfs_stat_t info;
    CHECK(vfs_stat("/embedded", &info) == 0);
    CHECK(info.st_mode.directory && info.st_mode.read_only);
    CHECK(vfs_chdir("/embedded") == 0);
    CHECK(vfs_stat("", &info) == 0);
    CHECK(info.st_mode.directory && info.st_mode.read_only);
    return EXIT_SUCCESS;
}
