# Scope and remaining work

Seventeen original-source cases using original CORE formatting and real declarations. Public registered commands/settings and captured report callbacks exercise ADC conversion, report changes, calibration, circuit correction, invalid sensor readings and alarm requests. Host analog port1 remaps to0, NVS and spindle/alarm boundaries are simulated. Registered direct float settings are assigned according to their declared datatype; this is not full settings-parser validation. ADC samples and alarms do not prove physical sensor accuracy or stopping latency. Port availability/getter/reboot-required metadata, pending disable and settings
restore have dedicated cases; active monitoring retains the existing claim until
reboot. No repeated load is used to conceal or force unresolved hook ownership.
No known assertion/diagnostic exceptions. Repeated settings-load hook ownership, malformed/trailing command parameters and sensor-error interruption of alarm sampling need separate contract review; do not force recursive hook failure.
