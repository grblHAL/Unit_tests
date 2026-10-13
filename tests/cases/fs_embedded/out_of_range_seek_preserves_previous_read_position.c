#include "support/embedded_seek_host.h"

int main(void)
{
    vfs_file_t *file = open_seek_fixture();
    CHECK(vfs_seek(file, 2) == 0);
    CHECK(vfs_seek(file, 6) == -1);
    CHECK(vfs_errno == EINVAL);
    CHECK(vfs_tell(file) == 2 && !vfs_eof(file));
    char data[4] = {0};
    CHECK(vfs_read(data, 1, 3, file) == 3);
    CHECK(strcmp(data, "llo") == 0);
    vfs_close(file);
    return EXIT_SUCCESS;
}
