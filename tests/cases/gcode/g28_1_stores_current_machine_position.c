#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char move[] = "G0X10Y20Z30";
    CHECK(gc_execute_block(move) == Status_OK);
    char store[] = "G28.1";
    CHECK(gc_execute_block(store) == Status_OK);
    coord_system_data_t saved;
    CHECK(settings_read_coord_data(CoordinateSystem_G28, &saved));
    NEAR(saved.coord.x, 10);
    NEAR(saved.coord.y, 20);
    NEAR(saved.coord.z, 30);
    return EXIT_SUCCESS;
}
