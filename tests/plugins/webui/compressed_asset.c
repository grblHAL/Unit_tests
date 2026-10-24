#include "webui_host.h"
int main(void)
{
    add_embedded_files();
    vfs_file_t *file = vfs_open("/embedded/index.html.gz", "r");
    CHECK(file);
    uint8_t data[512];
    size_t total = 0;
    size_t n = vfs_read(data, 1, sizeof(data), file);
    CHECK(n == 512 && data[0] == 0x1F && data[1] == 0x8B && data[2] == 8);
    total += n;
    while ((n = vfs_read(data, 1, sizeof(data), file)))
        total += n;
    CHECK(total == 11149 && vfs_eof(file));
    vfs_close(file);
    return 0;
}
