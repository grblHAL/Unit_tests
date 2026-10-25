#include "plasma_host.h"
#define CONFIG                                                                                     \
    "[MATERIAL_NUMBER_4]\nPIERCE_HEIGHT=3\nPIERCE_DELAY=0.5\nCUT_SPEED=900\nCUT_HEIGHT=1\nNAME="   \
    "Steel\nTHC=1\n"
static const embedded_file_t config = {
    .name = "linuxcnc/material.cfg", .size = sizeof(CONFIG) - 1, .data = CONFIG};
static const embedded_file_t *files[] = {&config, NULL};
static unsigned found;
static bool visit(material_t *m, void *data)
{
    CHECK(data == &found && m->id == 4 && !strcmp(m->name, "Steel") && m->thc_status);
    CHECK(m->pierce_height == 3 && m->pierce_delay == 0.5f && m->cut_height == 1 &&
          m->feed_rate == 900);
    found++;
    return false;
}
int main(void)
{
    plasma_prepare(3, true);
    plasma_load();
    plasma_mount(files);
    CHECK(!plasma_enumerate_materials(visit, &found) && found == 1);
    return 0;
}
