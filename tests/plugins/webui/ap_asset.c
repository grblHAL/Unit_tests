#include "webui_host.h"
int main(void)
{
    add_embedded_files();
    vfs_file_t *file = vfs_open("/embedded/ap_login.html", "r");
    CHECK(file);
    char data[64] = {0};
    CHECK(vfs_read(data, 1, 63, file) == 63);
    CHECK(strncmp(data, "<!DOCTYPE html>", 15) == 0);
    vfs_close(file);
    return 0;
}
