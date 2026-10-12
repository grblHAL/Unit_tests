#include "fs_embedded.h"
#include "support/backend_close.h"
#include "check.h"
static const embedded_file_t first = {.name = "first", .size = 3, .data = {'a','b','c'}};
static const embedded_file_t hidden = {.name = "hidden", .size = 2, .st_mode = {.hidden = true}, .data = {'x','y'}};
static const embedded_file_t second = {.name = "second", .size = 1, .data = {'z'}};
static const embedded_file_t *files[] = {&hidden, &first, NULL};
static const embedded_file_t *more[] = {&second, NULL};

int main(void)
{
    fs_embedded_mount(files);
    vfs_free_t *space = vfs_fgetfree("/embedded/");
    CHECK(space != NULL && space->used == 5 && space->size == 5);
    fs_embedded_mount(more);
    space = vfs_fgetfree("/embedded/");
    CHECK(space != NULL && space->used == 6 && space->size == 6);
    return EXIT_SUCCESS;
}
