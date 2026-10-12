#include "fs_embedded.h"
#include "support/backend_close.h"
#include <string.h>
#include "check.h"
static const embedded_file_t fixture = {.name = "hello.txt", .size = 5, .data = {'h', 'e', 'l', 'l', 'o'}};
static const embedded_file_t *files[] = {&fixture, NULL};
int main(void)
{
    fs_embedded_mount(files);
    vfs_file_t *file = vfs_open("/embedded/hello.txt", "r");
    char data[6] = {0};
    CHECK(file != NULL);
    CHECK(vfs_read(data, 1, 2, file) == 2);
    CHECK(strncmp(data, "he", 2) == 0);
    CHECK(vfs_tell(file) == 2);
    CHECK(!vfs_eof(file));
    CHECK(vfs_read(data, 1, 6, file) == 3);
    CHECK(strncmp(data, "llo", 3) == 0);
    CHECK(vfs_eof(file));
    backend_close(file);
    return EXIT_SUCCESS;
}
