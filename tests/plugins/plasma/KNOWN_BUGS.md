# Known defects and scope

No runtime defect is classified for these tested plasma scenarios.
Original plasma source d2f91b5887db6550ddec0fc0229cd87ec0af1a56 and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f are unchanged.

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
production type alias or source patch is used. No sanitizer allowance and no
whole-plugin coverage claim.

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
