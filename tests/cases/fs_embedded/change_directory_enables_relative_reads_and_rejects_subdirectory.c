#include "fs_embedded.h"
#include "support/backend_close.h"
#include "check.h"
static const embedded_file_t first = {.name = "first", .size = 3, .data = {'a','b','c'}};
static const embedded_file_t hidden = {.name = "hidden", .size = 2, .st_mode = {.hidden = true}, .data = {'x','y'}};
static const embedded_file_t *files[] = {&hidden, &first, NULL};

int main(void)
{
    fs_embedded_mount(files);
    CHECK(vfs_chdir("/embedded") == 0);
    CHECK(vfs_chdir("/embedded/missing") == -1);
    vfs_file_t *file = vfs_open("first", "r");
    CHECK(file != NULL);
    char data[4] = {0};
    CHECK(vfs_read(data, 1, 3, file) == 3);
    CHECK(strcmp(data, "abc") == 0);
    backend_close(file);
    return EXIT_SUCCESS;
}
