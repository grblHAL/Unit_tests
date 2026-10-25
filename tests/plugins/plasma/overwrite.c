#include "plasma_host.h"
static unsigned calls;
static bool visit(material_t *m, void *data)
{
    CHECK(data == &calls && m->id == 4 && m->feed_rate == 1200 && !strcmp(m->name, "New steel"));
    calls++;
    return false;
}
int main(void)
{
    plasma_prepare(3, true);
    plasma_load();
    material_t m = plasma_material(4);
    CHECK(plasma_material_add(&m, false));
    m.feed_rate = 1200;
    strcpy(m.name, "New steel");
    CHECK(plasma_material_add(&m, false));
    CHECK(plasma_list() == Status_OK && strstr(plasma_output, "fr:900") &&
          !strstr(plasma_output, "New steel"));
    CHECK(plasma_material_add(&m, true));
    CHECK(!plasma_enumerate_materials(visit, &calls) && calls == 1);
    return 0;
}
