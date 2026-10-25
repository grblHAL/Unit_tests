#include "plasma_host.h"
static unsigned found;
static bool visit(material_t *m, void *data)
{
    CHECK(data == &found && m->id == 4 && m->pierce_height == 3);
    found++;
    return false;
}
int main(void)
{
    plasma_prepare(3, true);
    plasma_load();
    material_t m = plasma_material(4);
    CHECK(plasma_material_is_valid(&m) && plasma_material_add(&m, false));
    CHECK(!plasma_enumerate_materials(visit, &found) && found == 1);
    CHECK(plasma_list() == Status_OK && strstr(plasma_output, "nu:4") &&
          strstr(plasma_output, "na:Steel"));
    return 0;
}
