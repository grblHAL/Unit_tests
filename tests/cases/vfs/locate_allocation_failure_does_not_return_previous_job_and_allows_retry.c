#include "support/vfs_locate_host.h"
#include "support/realloc_failure_host.h"

int main(void)
{
    mount_lookup_sources(true, false, false);
    root_found = true;
    fail_realloc = true;
    const char *initial_failure = vfs_locate_file("workbee_panel_fixture_01.nc");
    fail_realloc = false;
    CHECK(initial_failure == NULL);
    CHECK(failed_realloc_calls == 1 && lookup_count == 0);
    const char *path = vfs_locate_file("panel.nc");
    CHECK(path && strcmp(path, "/panel.nc") == 0);
    CHECK(lookup_count == 1);
    fail_realloc = true;
    const char *failed_path = vfs_locate_file("workbee_panel_fixture_01.nc");
    fail_realloc = false;
    CHECK(failed_realloc_calls == 2 && lookup_count == 1);
    fprintf(stderr, "Failed filename lookup returned %s\n", failed_path ? failed_path : "NULL");
    bool rejected = failed_path == NULL;
    path = vfs_locate_file("workbee_panel_fixture_01.nc");
    CHECK(path && strcmp(path, "/workbee_panel_fixture_01.nc") == 0);
    CHECK(lookup_count == 2 && failed_realloc_calls == 2);
    unmount_lookup_sources(true, false, false);
    CHECK(rejected);
    return EXIT_SUCCESS;
}
