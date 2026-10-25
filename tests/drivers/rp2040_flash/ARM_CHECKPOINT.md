# RP2040 serial ARM checkpoint - 2026-10-25

This is an unregistered compile probe saved for continuation. It adds no unit
cases or source coverage and is not wired into CI.

Original driver revision: `2f5bc4a06ecea3b1f78c1644623810f9b6416376`.
CORE revision: `b01f481072edecac33d5e40c25869359a5b3fa1f`.
Pico SDK 2.1.1: `bddd20f928ce76142793bef434d4f75f4af6e433` (installed checkout verified clean).
Compiler: Arm GNU Toolchain 14.2.Rel1 / GCC 14.2.1.
Board: `pico` / Cortex-M0+.

The original serial.c and SDK dependencies compile as ARM objects. The serial
object was verified as ELF32 little-endian ARM relocatable. No firmware link,
controller execution or hardware test was performed. Original warnings include
serialDisable returning no value and an unused tx_fifo_size; this probe does
not validate those runtime paths.

Source SHA256: `0592126d0b39d745fce7cb231da14bc3b6cc711f1d14a91f4734976f92b10de9`.
Serial object SHA256: `0b3abc8277a279cfe1ddc167d6acfcaf00e303fe53197eef44697b83ac4e1133`.

The initial probe omitted the platform defines. The final probe uses RP2040
and NEW_FATFS exactly as the driver's own CMakeLists.txt defines them, plus
RP_MCU=2040 and the selected standalone serial configuration below. No source,
SDK function, register layout, instruction or compatibility alias was changed.

Runtime gap: RX consumes DR in a loop until real hardware changes FR.RXFE;
plain mapped RAM cannot supply FIFO read side effects. The SDK host UART layer
has an incomplete register type and does not match these direct register uses.
Do not replace its accessors or force private queues to claim native UART proof.
A faithful peripheral emulator or hardware is still needed. RP2350, alternate
UARTs, PIO UARTs and full board linking remain unchecked.

Local evidence is under build-evidence/pico-arm-batch50-*: configure/build logs,
compile_commands.json, objects and pico-arm-batch50-evidence.json. These local
build outputs are ignored. The complete probe project is preserved here; it was
run from build-evidence/pico-arm-batch50-src/CMakeLists.txt, whose ../.. resolves
to the harness root. SDK/toolchain paths were supplied through CMake options.

```cmake
cmake_minimum_required(VERSION 3.20)
include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")
project(grblhal_pico_module_probe LANGUAGES C CXX ASM)
pico_sdk_init()
get_filename_component(HARNESS_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/grbl")
file(GLOB headers "${HARNESS_ROOT}/core/*.h")
foreach(header IN LISTS headers)
 get_filename_component(name "${header}" NAME)
 file(CONFIGURE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/grbl/${name}" CONTENT "#include \"${header}\"\n" @ONLY)
endforeach()
add_library(driver_serial OBJECT "${HARNESS_ROOT}/drivers/rp2040/serial.c")
target_include_directories(driver_serial PRIVATE "${HARNESS_ROOT}/drivers/rp2040" "${CMAKE_CURRENT_BINARY_DIR}/include")
if(PICO_PLATFORM STREQUAL "rp2040")
 target_compile_definitions(driver_serial PRIVATE RP_MCU=2040)
else()
 target_compile_definitions(driver_serial PRIVATE RP_MCU=2350)
endif()
target_compile_definitions(driver_serial PRIVATE RP2040 NEW_FATFS OVERRIDE_MY_MACHINE=1 USB_SERIAL_CDC=0 MPG_BUFFER_SIZE=0 RX_BUFFER_SIZE=32 TX_BUFFER_SIZE=32)
target_compile_options(driver_serial PRIVATE -Wall -Wextra)
target_link_libraries(driver_serial PRIVATE pico_stdlib hardware_uart hardware_irq hardware_pio cmsis_core)
```

Next: establish a locked SDK dependency and portable ARM check, validate a fresh
SDK checkout without relying on installed submodules, then assess supported
RP2350/secondary configurations. Keep compile counts separate from unit tests.
