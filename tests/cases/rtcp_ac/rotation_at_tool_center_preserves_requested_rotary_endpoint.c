#include "support/rtcp_segment_host.h"
int main(void)
{
    prepare_rtcp(); zero_rtcp_centers(); rtcp_command(851);
    coord_data_t target = {.c = 90}, last;
    CHECK(complete_rtcp_segment(&target, &last) == 1);
    NEAR(last.x, 0); NEAR(last.y, 0); NEAR(last.z, 0);
    fprintf(stderr, "Requested C=90, emitted C=%g\n", (double)last.c);
    NEAR(last.a, 0); NEAR(last.c, 90);
    return EXIT_SUCCESS;
}
