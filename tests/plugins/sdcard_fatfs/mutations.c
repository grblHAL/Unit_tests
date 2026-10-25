#include "fatfs_host.h"
int main(void)
{
    fatfs_prepare();
    vfs_file_t *f = vfs_open("/OLD.NC", "w");
    CHECK(f);
    CHECK(vfs_write("123456789", 1, 9, f) == 9);
    CHECK(vfs_truncate(f, 4) == FR_OK);
    vfs_close(f);
    CHECK(vfs_rename("/OLD.NC", "/NEW.NC") == FR_OK);
    f = vfs_open("/NEW.NC", "r");
    CHECK(f && f->size == 4);
    char text[8] = {0};
    CHECK(vfs_read(text, 1, sizeof(text), f) == 4 && !strcmp(text, "1234"));
    vfs_close(f);
    CHECK(vfs_unlink("/NEW.NC") == FR_OK && !vfs_open("/NEW.NC", "r"));
    return 0;
}
