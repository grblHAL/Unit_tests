# Known defects and scope

## Material listing overflows its label buffer

Confirmed 2026-11-24 on Plugin_plasma `5608649a18f7821f7d2ecbc1dd0c45d189113d03`
and CORE `a53a16a4d756f12a27006152ba3a99b5ec46b2c7`, Windows Clang ASan and hosted Linux GCC/Clang ASan.
`$EM` listing of an ordinary material reaches
[ml_enumerate](https://github.com/grblHAL/Plugin_plasma/blob/5608649a18f7821f7d2ecbc1dd0c45d189113d03/thc.c#L678).
Its three-byte lbl buffer receives the three-character `ph=` token and its
terminating NUL from strgetentry, causing a stack-buffer-overflow at
[CORE strutils.c:179](https://github.com/grblHAL/core/blob/a53a16a4d756f12a27006152ba3a99b5ec46b2c7/strutils.c#L179).

The existing materials, comments, overwrite and comment_rejection tests retain
their correct assertions. Sanitizer builds use the exact test/source/line/function/
diagnostic matcher in [known_sanitizer_diagnostics.json](known_sanitizer_diagnostics.json)
through known_crash.py, with named WILL_FAIL/known_crash registrations in
[CMakeLists.txt](CMakeLists.txt). Unrelated crashes or missing diagnostics fail.
Assertions after the fatal listing are unvalidated. Hosted run45362565627 passes
the exact Clang matcher; the previous run45357783766 passes both GCC and Clang.
No diagnostic matcher is broadened.

The same unchanged source also corrupts the uninstrumented Linux GCC coverage
listing. Run45362565627 first verifies via public enumeration that rejected
overwrite retained feed900 and name Steel, then reports
`[MATERIAL:o:2|nu:4|na:Steel|th:130.59001]`: parameter labels and separators are
missing. In ml_enumerate, lbl's out-of-bounds terminator can overwrite the
adjacent el separator buffer. The retained correct fr:900 assertion fails.
Only plugin_plasma.overwrite in Linux/GNU coverage without sanitizers has a
WILL_FAIL/known_bug allowance for this same defect. Other plain cases remain
ordinary tests. Post-list overwrite assertions remain unvalidated in this job.

After a source fix, remove the four sanitizer wrappers and manifest objects,
the exact coverage allowance, and this defect section. Retain all tests and run
the complete GCC/Clang sanitizer suite, coverage and strict summary. No production
source is patched.

## Tested scope

Real CORE I/O registration, secondary-stepper allocation/configuration, PID,
VFS/embedded file backend and actual EEPROM/CRC provider are compiled. The host
supplies driver pins, clock and step callbacks through public interfaces. Tests
use initial Off mode or boot Arc-ok/Up-down/Voltage modes from bytes saved by the
registered EEPROM provider. No private init_ok or state handler is set.
I/O and plasma settings register separately, with distinct allocated NVS ranges.
LinuxCNC/SheetCam files are read through the actual VFS mount listeners; the
read-only embedded backend is exposed at / through the public mount API.

Cases cover dependency failures, material validity/add/overwrite/enumeration,
material comments/rejection/recovery, registered material listing, report hooks
and both file imports. Runtime cases cover arc start/stop, three failed ignition
attempts, successful third retry, lost-arc hold requests, directional secondary-Z
steps, velocity lock/recovery and reset. A separate process saves the registered
mode setting because it requires reboot. Actual CORE spindle registration and
secondary-stepper polling run against simulated driver pins/time. The controller
boundary observes feed-hold requests; full CORE suspend/automatic torch shutdown,
primary XY motion, pierce/cut-height moves, PowerMax,
expression integration and physical timing remain untested.

Original plugin/CORE warnings remain visible under -Wno-error; fixtures retain
-Werror. MinGW exports isnanf in its math runtime without a math.h declaration,
so the host driver header declares it on Windows. No replacement implementation,
production type alias or source patch is used. The listing exception above does
not establish the assertions after its crash or whole-plugin coverage.

Batch40 adds five voltage-mode workflows plus EEPROM boot setup/cleanup,30 cases
total. A real CORE analog-input bank exposes a host voltage callback; voltage port
is assigned through the registered float setter, saved by the original EEPROM,
and loaded in a fresh process. Original PID and secondary-stepper pulses verify
low/high-voltage direction, stable band, velocity lock/resume, reset, calibrated
report values and lost-arc hold. Controller timing/input voltage remain models;
no actual electrical scaling or closed-loop cut-quality claim is made.

Original powermax.c is gated by `#if PLASMA_ENABLE && 0`; it is not a runnable
module in this source. It was not enabled by rewriting a guard or copying its
functions into a test. Powermax communication remains unavailable/unvalidated.
