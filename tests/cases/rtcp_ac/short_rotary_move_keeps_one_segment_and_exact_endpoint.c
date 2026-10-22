#include "support/rtcp_segment_host.h"
int main(void)
{
    prepare_rtcp(); zero_rtcp_centers();
    sys.position[X_AXIS] = 80;
    rtcp_command(851);
    coord_data_t target = {.x = 1, .c = .001f}, last;
    CHECK(complete_rtcp_segment(&target, &last) == 1);
    NEAR(last.x, cosf(.001f * (float)M_PI / 180));
    NEAR(last.y, sinf(.001f * (float)M_PI / 180));
    NEAR(last.c, .001f);
    return EXIT_SUCCESS;
}
