#include "plasma_host.h"
static unsigned calls;
static bool visit(material_t *m, void *data)
{
    CHECK(data == &calls && m->id == 4);
    calls++;
    return true;
}
int main(void)
{
    plasma_prepare(3, true);
    plasma_load();
    material_t a = plasma_material(4), b = plasma_material(7);
    CHECK(plasma_material_add(&a, false) && plasma_material_add(&b, false));
    CHECK(plasma_enumerate_materials(visit, &calls) && calls == 1);
    return 0;
}
