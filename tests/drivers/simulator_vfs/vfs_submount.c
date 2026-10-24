#include "vfs_host.h"
int main(void)
{
 sim_prepare("/jobs"); sim_put("/jobs/part.ngc", "M2"); sim_expect("/jobs/part.ngc", "M2");
 CHECK(vfs_open("/part.ngc", "rb") == NULL); CHECK(vfs_chdir("/jobs") == 0); sim_expect("part.ngc", "M2");
 char cwd[32]; CHECK(vfs_getcwd(cwd, sizeof(cwd)) && strcmp(cwd, "/jobs") == 0);
 CHECK(vfs_unlink("part.ngc") == 0); sim_finish("/jobs"); CHECK(vfs_open("/jobs/part.ngc", "rb") == NULL); return 0;
}
