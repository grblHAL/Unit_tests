# Known defects and scope

No runtime defects are currently classified for the selected seven VFD protocol
configurations. Source grblHAL/Plugins_spindle
8a3ae47f5a218834da9c742424c3dd22c5629fdb, CORE
b01f481072edecac33d5e40c25869359a5b3fa1f. No production-source changes.

Tests compile the original VFD coordinator and seven protocol handlers with real
CORE spindle registration/selection, at-speed conversion, Modbus interface
registration and EEPROM/CRC persistence. A registered simulated RTU transport
observes command bytes and supplies replies, rejected sends and exceptions.
These are not physical VFD, serial-timing or full parser/motion tests. Additional
VFD configurations, spindle output/stepper/selection variants and multiple spindles
remain inventory work; no whole-repository coverage claim.

Original plugin/CORE format, enum and unused-argument warnings remain visible
under the main harness's production-code -Wno-error policy. Host fixtures keep
-Werror; no sanitizer exceptions and no clean-Werror source claim. Feedback
checks allow 0.01 RPM of floating-point conversion noise while still checking
exact Modbus register/value bytes. Persistent restart cases use two real
processes and the original EEPROM backend, not a copied private NVS layout.
