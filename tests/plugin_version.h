#pragma once
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// A plugin's reported version must be present and well formed ("1.2", "0.5.0"),
// but tests must not pin the exact value: plugin authors bump it independently of
// this harness, and an exact match turns every release into a harness failure.
static inline bool plugin_version_valid (const char *version)
{
    if (version == NULL || !isdigit((unsigned char)*version))
        return false;

    unsigned dots = 0;
    for (const char *s = version; *s; s++) {
        if (*s == '.') {
            if (!isdigit((unsigned char)s[1]))
                return false;
            dots++;
        } else if (!isdigit((unsigned char)*s) && !isalpha((unsigned char)*s))
            return false;
    }

    return dots > 0;
}

// Same as plugin_version_valid, and the version must start with major (e.g. "2.").
static inline bool plugin_version_major (const char *version, const char *major)
{
    size_t n = strlen(major);
    return plugin_version_valid(version) && strncmp(version, major, n) == 0 && version[n] == '.';
}
