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
    char data = 'x';
    CHECK(file != NULL);
    CHECK(vfs_read(&data, 1, 0, file) == 0);
    CHECK(data == 'x');
    CHECK(vfs_tell(file) == 0);
    backend_close(file);
    return EXIT_SUCCESS;
}
