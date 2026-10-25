#include "vfs_host.h"
int main(void)
{
 sim_prepare("/"); sim_put("/kept.ngc", "M2");
 CHECK(vfs_chmod("/kept.ngc", (vfs_st_mode_t){.read_only = On}, (vfs_st_mode_t){.read_only = On}) != 0);
 struct tm modified = {.tm_year = 126, .tm_mon = 0, .tm_mday = 1}; CHECK(vfs_utime("/kept.ngc", &modified) != 0);
 CHECK(vfs_fgetfree("/") == NULL); vfs_drive_t *drive = vfs_get_drive("/"); CHECK(drive && vfs_drive_format(drive) != 0);
 sim_expect("/kept.ngc", "M2"); CHECK(vfs_unlink("/kept.ngc") == 0); sim_finish("/"); return 0;
}
