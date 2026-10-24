# Scope and remaining work

Eighteen original-source lifecycle cases with real CORE declarations. Host NVS, public port-configuration callbacks, spindle readback and delayed-task boundaries capture behavior. Port claim remaps configured port1 to output0. Timer expiration is explicitly delivered by the host, not a real timing/scheduler measurement. Setting callbacks come from the actual registered table. Covers active/idle/pause transitions, programmed M5 before hardware change, program completion, reset, reload without second claim, unavailable resources and hook chaining. Additional registered getters/save/load/restore cases verify default and changed
timeouts/masks plus pending port changes across reload. The advertised reboot
requirement is checked; no actual reboot or physical port reassignment is proved.
No known assertion/diagnostic exceptions. Full settings parser/task scheduler/physical air-pressure behavior remain untested.

Cumulative batch22 validates18 cases; selected-source140/141 lines and43/52
branches. The inactive-port early return is not forced via private state.
