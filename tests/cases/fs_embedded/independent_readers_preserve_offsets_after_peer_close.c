#include "fs_embedded.h"
#include "check.h"
#include <string.h>
static const embedded_file_t first = {.name = "first", .size = 5, .data = {'a','b','c','d','e'}};
static const embedded_file_t *files[] = {&first, NULL};
int main(void)
{
    fs_embedded_mount(files);
    vfs_file_t *left = vfs_open("/embedded/first", "r");
    vfs_file_t *right = vfs_open("/embedded/first", "r");
    CHECK(left != NULL && right != NULL && left != right);
    char data[6] = {0};
    CHECK(vfs_read(data, 1, 2, left) == 2 && memcmp(data, "ab", 2) == 0);
    CHECK(vfs_seek(right, 3) == 0);
    CHECK(vfs_read(data, 1, 2, right) == 2 && memcmp(data, "de", 2) == 0);
    CHECK(vfs_eof(right) && vfs_tell(left) == 2);
    vfs_close(right);
    CHECK(vfs_read(data, 1, 3, left) == 3 && memcmp(data, "cde", 3) == 0);
    vfs_close(left);
    left = vfs_open("/embedded/first", "r");
    CHECK(left != NULL && vfs_tell(left) == 0 && !vfs_eof(left));
    vfs_close(left);
    return EXIT_SUCCESS;
}
