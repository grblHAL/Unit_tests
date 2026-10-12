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
    char data[4] = {0};
    CHECK(file != NULL);
    CHECK(vfs_seek(file, 2) == 0);
    CHECK(vfs_tell(file) == 2);
    CHECK(vfs_read(data, 1, 3, file) == 3);
    CHECK(strcmp(data, "llo") == 0);
    backend_close(file);
    return EXIT_SUCCESS;
}
