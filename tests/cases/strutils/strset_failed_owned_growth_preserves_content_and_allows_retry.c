#include "support/string_allocation_host.h"
int main(void)
{
    char storage[8] = "old.nc";
    const char *job = "workbee_panel_fixture_01.nc";
    const char *longer = "workbee_panel_fixture_01_finishing_pass.nc";
    string_t base = {.data = storage, .len = sizeof(storage) - 1};
    string_t text = {.base = &base};
    CHECK(strset(&text, strlen(job), job) != NULL);
    tracked_allocation = text.data;
    size_t capacity = text.len;
    reject_growth = true;
    CHECK(strset(&text, strlen(longer), longer) == NULL);
    CHECK(rejected_growths == 1 && tracked_frees == 0);
    CHECK(text.data == tracked_allocation && text.len == capacity);
    CHECK(strcmp(text.data, job) == 0);
    CHECK(strcmp(storage, "old.nc") == 0);
    CHECK(strset(&text, strlen(longer), longer) != NULL);
    CHECK(text.data != storage && strcmp(text.data, longer) == 0);
    tracked_allocation = NULL;
    free(text.data);
    return EXIT_SUCCESS;
}
