#include "vfs_host.h"
int main(void)
{
 sim_prepare("/"); CHECK(vfs_open("/absent.ngc", "rb") == NULL);
 CHECK(vfs_mkdir("/jobs") == 0 && vfs_chdir("/jobs") == 0);
 CHECK(vfs_chdir("/absent") != 0); char cwd[32]; CHECK(vfs_getcwd(cwd, sizeof(cwd)) && strcmp(cwd, "/jobs") == 0);
 sim_put("kept.ngc", "M2"); CHECK(vfs_rename("absent.ngc", "new.ngc") != 0 && vfs_unlink("absent.ngc") != 0);
 sim_expect("kept.ngc", "M2"); CHECK(vfs_chdir("kept.ngc") != 0); CHECK(vfs_unlink("kept.ngc") == 0);
 CHECK(vfs_chdir("/") == 0 && vfs_rmdir("/jobs") == 0); sim_finish("/"); return 0;
}
