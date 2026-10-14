#include "support/rtcp_segment_host.h"

int main(void)
{
    prepare_rtcp(); zero_rtcp_centers(); rtcp_command(851);
    coord_data_t target = {.x = 10, .c = 90}, last;
    CHECK(complete_rtcp_segment(&target, &last) > 1);
    NEAR(last.x, 0); NEAR(last.y, 10); NEAR(last.c, 90);
    target.c = 180;
    CHECK(complete_rtcp_segment(&target, &last) > 1);
    NEAR(last.x, -10); NEAR(last.y, 0); NEAR(last.c, 180);
    NEAR(target.x, 10); NEAR(target.c, 180);
    return EXIT_SUCCESS;
}
