#include "cluster_host.h"
int main(void)
{
    cluster_prepare(false, "G1X10F600S10:20\n");
    char out[128];
    cluster_drain(out, sizeof(out));
    CHECK(!strcmp(out, "G1X5F600S10\nG1X5S20\nG1X0S10\n"));
    CHECK(cluster_statuses == 1);
    return 0;
}
