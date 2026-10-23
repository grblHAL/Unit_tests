#include "support/string_allocation_host.h"
int main(void)
{
    string_t text = {0};
    const char *job = "panel_roughing.nc";
    const char *next = "panel_finishing_with_tabs.nc";
    reject_growth = true;
    CHECK(strset(&text, strlen(job), job) == NULL);
    CHECK(text.data == NULL && text.len == 0);
    CHECK(rejected_growths == 1 && tracked_frees == 0);
    CHECK(strset(&text, strlen(job), job) != NULL);
    CHECK(strcmp(text.data, job) == 0);
    tracked_allocation = text.data;
    reject_growth = true;
    CHECK(strset(&text, strlen(next), next) == NULL);
    CHECK(text.data == NULL && text.len == 0);
    CHECK(rejected_growths == 2 && tracked_frees == 1);
    tracked_allocation = NULL;
    CHECK(strset(&text, strlen(next), next) != NULL);
    CHECK(strcmp(text.data, next) == 0 && text.len >= strlen(next));
    free(text.data);
    return EXIT_SUCCESS;
}
