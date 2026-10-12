#include "fs_embedded.h"
#include "support/backend_close.h"
#include "check.h"
#include <errno.h>
static const embedded_file_t hidden = {.name = "hidden", .size = 2, .st_mode = {.hidden = true}, .data = {'x','y'}};
static const embedded_file_t *files[] = {&hidden, NULL};

int main(void)
{
    fs_embedded_mount(files);
    vfs_file_t *file = vfs_open("/embedded/hidden", "r");
    CHECK(file != NULL);
    char data[3] = {0};
    CHECK(vfs_read(data, 1, 2, file) == 2);
    CHECK(strcmp(data, "xy") == 0);
    backend_close(file);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/embedded/hidden", &st) == 0);
    CHECK(st.st_mode.hidden && st.st_mode.read_only && st.st_size == 2);
    return EXIT_SUCCESS;
}
