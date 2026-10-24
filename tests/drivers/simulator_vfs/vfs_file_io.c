#include "vfs_host.h"
int main(void)
{
 sim_prepare("/"); sim_put("/job.ngc", "G1X10\nM2\n");
 vfs_stat_t stat = {0}; CHECK(vfs_stat("/job.ngc", &stat) == 0 && stat.st_size == 9 && !stat.st_mode.directory);
 vfs_file_t *file = vfs_open("/job.ngc", "r+b"); CHECK(file && file->size == 9);
 char prefix[4] = {0}; CHECK(vfs_read(prefix, 1, 3, file) == 3 && strcmp(prefix, "G1X") == 0);
 CHECK(vfs_tell(file) == 3 && vfs_seek(file, 0) == 0 && vfs_tell(file) == 0);
 CHECK(vfs_truncate(file, 6) == 0); vfs_close(file); sim_expect("/job.ngc", "G1X10\n");
 CHECK(vfs_rename("/job.ngc", "/finished.ngc") == 0); CHECK(vfs_open("/job.ngc", "rb") == NULL);
 sim_expect("/finished.ngc", "G1X10\n"); CHECK(sim_changes >= 1);
 CHECK(vfs_unlink("/finished.ngc") == 0); sim_finish("/"); return 0;
}
