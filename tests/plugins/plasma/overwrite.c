#include "plasma_host.h"
static unsigned calls;
static bool original(material_t *m, void *data)
{
    CHECK(data == &calls && m->id == 4 && m->param.feed_rate == 900 && !strcmp(m->name, "Steel"));
    calls++;
    return false;
}
static bool visit(material_t *m, void *data)
{
    CHECK(data == &calls && m->id == 4 && m->param.feed_rate == 1200 && !strcmp(m->name, "New steel"));
    calls++;
    return false;
}
int main(void)
{
    plasma_prepare(3, true);
    plasma_load();
    material_t m = plasma_material(4);
    CHECK(plasma_material_add(&m, false));
    m.param.feed_rate = 1200;
    strcpy(m.name, "New steel");
    CHECK(!plasma_material_add(&m, false));
    CHECK(!plasma_enumerate_materials(original, &calls) && calls == 1);
    calls = 0;
    CHECK(plasma_list() == Status_OK);
    fprintf(stderr, "Original material listing: %s\n", plasma_output);
    CHECK(strstr(plasma_output, "fr:900") && !strstr(plasma_output, "New steel"));
    CHECK(plasma_material_add(&m, true));
    CHECK(!plasma_enumerate_materials(visit, &calls) && calls == 1);
    return 0;
}
