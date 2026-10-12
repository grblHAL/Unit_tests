#include "support/rtcp_host.h"
#include "check.h"

int main(void)
{
    prepare_rtcp();
    zero_rtcp_centers();
    rtcp_command(851);
    coord_data_t target = {.x = 10, .c = 90}, position = {0};
    plan_line_data_t data = {0};
    CHECK(kinematics.segment_line(&target, &position, &data, true) != NULL);
    coord_data_t last = {0}, *segment;
    unsigned segments = 0;
    while((segment = kinematics.segment_line(&target, &position, &data, false)) != NULL) {
        CHECK(++segments <= 1000);
        last = *segment;
    }
    CHECK(segments > 1);
    fprintf(stderr, "Endpoint X=%.3f Y=%.3f Z=%.3f C=%.3f\n", last.x, last.y, last.z, last.c);
    NEAR(last.c, 90);
    NEAR(last.x, 0);
    NEAR(last.y, 10);
    NEAR(last.z, 0);
    return EXIT_SUCCESS;
}
