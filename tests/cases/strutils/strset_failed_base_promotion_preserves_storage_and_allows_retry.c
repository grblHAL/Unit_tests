#include "support/string_allocation_host.h"
int main(void)
{
    char storage[8] = "old.nc";
    const char *job = "workbee_panel_fixture_01.nc";
    string_t base = {.data = storage, .len = sizeof(storage) - 1};
    string_t text = {.base = &base};
    reject_growth = true;
    CHECK(strset(&text, strlen(job), job) == NULL);
    CHECK(rejected_growths == 1 && tracked_frees == 0);
    CHECK(text.data == storage && text.len == base.len);
    CHECK(strcmp(storage, "old.nc") == 0);
    CHECK(strset(&text, strlen(job), job) != NULL);
    CHECK(text.data != storage && strcmp(text.data, job) == 0);
    CHECK(strcmp(storage, "old.nc") == 0);
    free(text.data);
    return EXIT_SUCCESS;
}
