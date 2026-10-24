#include "vfs_host.h"
int main(void)
{
 sim_prepare("/"); vfs_file_t *file = vfs_open("/edited.ngc", "wb"); CHECK(file);
 CHECK(vfs_write("ABCDEFGHIJ", 1, 10, file) == 10); CHECK(vfs_truncate(file, 4) == 0); vfs_close(file);
 vfs_stat_t stat = {0}; CHECK(vfs_stat("/edited.ngc", &stat) == 0); size_t size = stat.st_size;
 CHECK(vfs_unlink("/edited.ngc") == 0); sim_finish("/"); fprintf(stderr, "persisted length=%zu\n", size); CHECK(size == 4); return 0;
}
