#include "fs_embedded.h"
#include "support/backend_close.h"
#include "check.h"
static const embedded_file_t hidden = {.name = "private", .size = 2,
    .st_mode = {.hidden = true}, .data = {'x','y'}};
static const embedded_file_t visible = {.name = "visible", .size = 1, .data = {'z'}};
static const embedded_file_t *files[] = {&hidden, &visible, NULL};
int main(void)
{
    fs_embedded_mount(files);
    CHECK(vfs_chdir("/embedded") == 0);
    vfs_file_t *file = vfs_open("visible", "r");
    CHECK(file != NULL);
    backend_close(file);
    file = vfs_open("/embedded/private", "r");
    CHECK(file != NULL);
    char data[3] = {0};
    CHECK(vfs_read(data, 1, 2, file) == 2 && strcmp(data, "xy") == 0);
    backend_close(file);
    file = vfs_open("private", "r");
    bool relative_opened = file != NULL;
    if(file) backend_close(file);
    CHECK(!relative_opened);
    return EXIT_SUCCESS;
}
