#include "webui_host.h"
int main(void)
{
    add_embedded_files();
    CHECK(vfs_open("/embedded/ok.txt", "w") == NULL);
    vfs_file_t *file = vfs_open("/embedded/ok.txt", "r");
    CHECK(file);
    CHECK(vfs_write("bad", 1, 3, file) == 0);
    vfs_close(file);
    file = vfs_open("/embedded/ok.txt", "r");
    CHECK(file);
    char text[2];
    CHECK(vfs_read(text, 1, 2, file) == 2 && memcmp(text, "ok", 2) == 0);
    vfs_close(file);
    return 0;
}
