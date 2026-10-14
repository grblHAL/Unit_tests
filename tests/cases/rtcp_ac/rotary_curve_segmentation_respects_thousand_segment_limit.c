#include "support/rtcp_segment_host.h"

int main(void)
{
    prepare_rtcp(); zero_rtcp_centers();
    char length[] = "0.010";
    CHECK(settings_store_setting(Setting_Kinematics6, length) == Status_OK);
    sys.position[X_AXIS] = 800; rtcp_command(851);
    coord_data_t target = {.x = 10, .c = 90}, last;
    CHECK(complete_rtcp_segment(&target, &last) == 1000);
    NEAR(last.x, 0); NEAR(last.y, 10); NEAR(last.c, 90);
    return EXIT_SUCCESS;
}
