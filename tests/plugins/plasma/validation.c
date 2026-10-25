#include "plasma_host.h"
int main(void)
{
    material_t m = plasma_material(1);
    CHECK(plasma_material_is_valid(&m));
    m.pierce_height = NAN;
    CHECK(!plasma_material_is_valid(&m));
    m = plasma_material(1);
    m.jump_height = 50;
    CHECK(!plasma_material_is_valid(&m));
    m.jump_height = 150;
    CHECK(plasma_material_is_valid(&m));
    m.id = 1000000;
    CHECK(!plasma_material_is_valid(&m));
    return 0;
}
