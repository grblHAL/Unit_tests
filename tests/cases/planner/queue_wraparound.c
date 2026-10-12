#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); plan_line_data_t data = {.feed_rate = 100}; float target[N_AXIS] = {0};
    for(unsigned round = 0; round < 4; round++) {
        for(unsigned i = 1; i <= 16; i++) { target[0] = (float)(round * 16 + i); data.line_number = round * 16 + i; CHECK(plan_buffer_line(target, &data)); }
        for(unsigned i = 1; i <= 16; i++) { CHECK(plan_get_current_block()->line_number == round * 16 + i); plan_discard_current_block(); }
        CHECK(plan_get_current_block() == NULL); CHECK(plan_get_block_buffer_available() == 16);
    }
    return EXIT_SUCCESS;
}
