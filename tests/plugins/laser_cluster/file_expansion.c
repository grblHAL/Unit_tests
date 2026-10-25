#include "cluster_host.h"
int main(void)
{
    cluster_prepare(true, "G1X1S5:10\nM5\n");
    char out[128];
    cluster_drain(out, sizeof(out));
    CHECK(!strcmp(out, "G1X0.5S5\nG1X0.5S10\nG1X0S5\nM5\n"));
    CHECK(cluster_statuses == 2);
    return 0;
}
