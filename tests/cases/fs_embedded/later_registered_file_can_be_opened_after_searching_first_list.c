#include "fs_embedded.h"
#include "check.h"
#include <string.h>
static const embedded_file_t first = {.name = "first", .size = 3, .data = {'a','b','c'}};
static const embedded_file_t second = {.name = "second", .size = 2, .data = {'x','y'}};
static const embedded_file_t third = {.name = "third", .size = 1, .data = {'z'}};
static const embedded_file_t *files[] = {&first, &second, NULL};
static const embedded_file_t fourth = {.name = "fourth", .size = 1, .data = {'q'}};
static const embedded_file_t fifth = {.name = "fifth", .size = 1, .data = {'r'}};
/* A longer second list keeps the regression deterministic without an invalid read.
   A one-entry second list additionally reproduces ASan global-buffer-overflow. */
static const embedded_file_t *more[] = {&third, &fourth, &fifth, NULL};
int main(void)
{
    fs_embedded_mount(files);
    fs_embedded_mount(more);
    vfs_file_t *file = vfs_open("/embedded/third", "r");
    CHECK(file != NULL);
    char data = 0;
    CHECK(vfs_read(&data, 1, 1, file) == 1 && data == 'z');
    CHECK(vfs_eof(file));
    vfs_close(file);
    return EXIT_SUCCESS;
}
