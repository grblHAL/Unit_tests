#include "webui_host.h"
int main(void)
{
    add_embedded_files();
    vfs_file_t *file = vfs_open("/embedded/ok.txt", "r");
    CHECK(file);
    char text[3] = {0};
    CHECK(vfs_read(text, 1, 2, file) == 2 && strcmp(text, "ok") == 0);
    CHECK(vfs_eof(file));
    vfs_close(file);
    vfs_stat_t st;
    CHECK(vfs_stat("/embedded/ok.txt", &st) == 0 && st.st_size == 2 && st.st_mode.hidden &&
          st.st_mode.read_only);
#if WEBUI_INFLASH
    CHECK(vfs_stat("/embedded/favicon.ico", &st) == 0 && st.st_size == 1150);
    CHECK(vfs_stat("/embedded/index.html.gz", &st) == 0 && st.st_size == 11149);
#else
    CHECK(vfs_stat("/embedded/index.html.gz", &st) != 0);
#endif
#if WIFI_SOFTAP
    CHECK(vfs_stat("/embedded/ap_login.html", &st) == 0 && st.st_size == 3727);
#else
    CHECK(vfs_stat("/embedded/ap_login.html", &st) != 0);
#endif
    return 0;
}
