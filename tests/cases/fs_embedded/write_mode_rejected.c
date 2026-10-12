#include "fs_embedded.h"
#include "support/backend_close.h"
#include <string.h>
#include "check.h"
static const embedded_file_t fixture = {.name = "hello.txt", .size = 5, .data = {'h', 'e', 'l', 'l', 'o'}};
static const embedded_file_t *files[] = {&fixture, NULL};
int main(void)
{
    fs_embedded_mount(files);
    CHECK(vfs_open("/embedded/hello.txt", "w") == NULL);
    return EXIT_SUCCESS;
}
