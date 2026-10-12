#include "fs_embedded.h"
#include "support/backend_close.h"
#include <string.h>
#include "check.h"
static const embedded_file_t fixture = {.name = "hello.txt", .size = 5, .data = {'h', 'e', 'l', 'l', 'o'}};
static const embedded_file_t *files[] = {&fixture, NULL};
int main(void)
{
    fs_embedded_mount(files);
    vfs_stat_t info;
    CHECK(vfs_stat("/embedded/hello.txt", &info) == 0);
    CHECK(info.st_size == 5);
    CHECK(info.st_mode.read_only);
    CHECK(vfs_stat("/embedded/missing.txt", &info) != 0);
    return EXIT_SUCCESS;
}
