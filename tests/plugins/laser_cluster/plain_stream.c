#include "cluster_host.h"
int main(void)
{
    cluster_prepare(false, "M3S100\nG0X1\n");
    char out[128];
    cluster_drain(out, sizeof(out));
    CHECK(!strcmp(out, "M3S100\nG0X1\n") && cluster_statuses == 2);
    return 0;
}
