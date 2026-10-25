#include "cluster_host.h"
int main(void)
{
    cluster_prepare(false, "G1Y-3S40:40:40\n");
    char out[128];
    cluster_drain(out, sizeof(out));
    CHECK(!strcmp(out, "G1Y-1S40\nG1Y-1S40\nG1Y-1S40\n"));
    CHECK(cluster_statuses == 1);
    return 0;
}
