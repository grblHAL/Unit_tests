cmake_minimum_required(VERSION 3.20)
project(grblhal_trinamic_tests LANGUAGES C)
include(../../components.cmake)
if(NOT EXISTS "${HARNESS_ROOT}/deps/trinamic/tmc2209hal.h")
 message(FATAL_ERROR "Fetch the Trinamic source lock including the real library first")
endif()
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/trinamic")
file(GLOB headers "${HARNESS_ROOT}/deps/trinamic/*.h")
foreach(header IN LISTS headers)
 get_filename_component(name "${header}" NAME)
 file(CONFIGURE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/trinamic/${name}" CONTENT "#include \"${header}\"\n" @ONLY)
endforeach()
set(runtime_cases hold_current block_current idle_reduction poll_quiet warning_report warning_motion warning_recovery homing_rates homing_irq)
foreach(behavior ${runtime_cases} initialization current_command address_override no_storage bus_failure fault_irq setting_current microsteps bus_recovery base_setup_failure mode_toggle hook_chaining persist_write persist_read debug_report debug_selected prewarn_clear hybrid_threshold chopper chopper_rejections crc_recovery)
 component_case(plugin_trinamic.${behavior} ${behavior}.c tmc_host.c tmc_runtime.c "${HARNESS_ROOT}/plugins/motor/trinamic.c" "${HARNESS_ROOT}/deps/trinamic/tmc2209.c" "${HARNESS_ROOT}/deps/trinamic/tmc2209hal.c" "${HARNESS_ROOT}/deps/trinamic/common.c" "${HARNESS_ROOT}/plugins/eeprom/eeprom_24AAxxx.c" "${HARNESS_ROOT}/tests/plugins/eeprom/eeprom_host.c" "${COMPONENT_CORE_ROOT}/crc.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c")
 target_include_directories(plugin_trinamic.${behavior} PRIVATE "${HARNESS_ROOT}/plugins/motor" "${HARNESS_ROOT}/deps/trinamic" "${HARNESS_ROOT}/tests/plugins/eeprom" "${HARNESS_ROOT}/plugins/eeprom")
 target_compile_definitions(plugin_trinamic.${behavior} PRIVATE TRINAMIC_ENABLE=2209 TRINAMIC_I2C=0 TRINAMIC_MIXED_DRIVERS=0 EEPROM_ENABLE=128 EEPROM_IS_FRAM=1 NVS_SIZE=8192 NVS_SIZE_MAX=16384)
 if(behavior IN_LIST runtime_cases)
  target_compile_definitions(plugin_trinamic.${behavior} PRIVATE TRINAMIC_POLL_STATUS=1 TRINAMIC_DYNAMIC_CURRENT=1)
 endif()
endforeach()
set_source_files_properties("${HARNESS_ROOT}/plugins/motor/trinamic.c" "${HARNESS_ROOT}/deps/trinamic/tmc2209.c" "${HARNESS_ROOT}/deps/trinamic/tmc2209hal.c" "${HARNESS_ROOT}/deps/trinamic/common.c" PROPERTIES COMPILE_OPTIONS -Wno-error)


file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tmc-persistent")
set_tests_properties(plugin_trinamic.persist_write PROPERTIES FIXTURES_SETUP tmc_nvs)
set_tests_properties(plugin_trinamic.persist_read PROPERTIES FIXTURES_REQUIRED tmc_nvs)
set_tests_properties(plugin_trinamic.persist_write plugin_trinamic.persist_read PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tmc-persistent")

foreach(chip 2130 2240 2660 5160)
 set(chip_sources "${HARNESS_ROOT}/deps/trinamic/tmc${chip}.c" "${HARNESS_ROOT}/deps/trinamic/tmc${chip}hal.c")
 set_source_files_properties(${chip_sources} PROPERTIES COMPILE_OPTIONS -Wno-error)
 set(chip_cases spi_initialization current_command setting_current microsteps bus_recovery)
 if(chip EQUAL 2660)
  set(spi_source tmc_spi20_host.c)
  list(APPEND chip_cases spi20_capabilities)
 else()
  set(spi_source tmc_spi_host.c)
  list(APPEND chip_cases mode_toggle)
 endif()
 foreach(behavior ${chip_cases})
  set(target plugin_trinamic.${chip}_${behavior})
  component_case(${target} ${behavior}.c tmc_host.c tmc_runtime.c ${spi_source}
   "${HARNESS_ROOT}/plugins/motor/trinamic.c" ${chip_sources} "${HARNESS_ROOT}/deps/trinamic/common.c"
   "${HARNESS_ROOT}/plugins/eeprom/eeprom_24AAxxx.c" "${HARNESS_ROOT}/tests/plugins/eeprom/eeprom_host.c"
   "${COMPONENT_CORE_ROOT}/crc.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c")
  target_include_directories(${target} PRIVATE "${HARNESS_ROOT}/plugins/motor" "${HARNESS_ROOT}/deps/trinamic" "${HARNESS_ROOT}/tests/plugins/eeprom" "${HARNESS_ROOT}/plugins/eeprom")
  target_compile_definitions(${target} PRIVATE TRINAMIC_ENABLE=${chip} TRINAMIC_I2C=0 TRINAMIC_MIXED_DRIVERS=0 EEPROM_ENABLE=128 EEPROM_IS_FRAM=1 NVS_SIZE=8192 NVS_SIZE_MAX=16384)
 endforeach()
endforeach()

foreach(behavior uart_transport)
 set(target plugin_trinamic.2240_${behavior})
 component_case(${target} ${behavior}.c tmc_host.c tmc_runtime.c
  "${HARNESS_ROOT}/plugins/motor/trinamic.c" "${HARNESS_ROOT}/deps/trinamic/tmc2240.c"
  "${HARNESS_ROOT}/deps/trinamic/tmc2240hal.c" "${HARNESS_ROOT}/deps/trinamic/common.c"
  "${HARNESS_ROOT}/plugins/eeprom/eeprom_24AAxxx.c" "${HARNESS_ROOT}/tests/plugins/eeprom/eeprom_host.c"
  "${COMPONENT_CORE_ROOT}/crc.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c")
 target_include_directories(${target} PRIVATE "${HARNESS_ROOT}/plugins/motor" "${HARNESS_ROOT}/deps/trinamic" "${HARNESS_ROOT}/tests/plugins/eeprom" "${HARNESS_ROOT}/plugins/eeprom")
 target_compile_definitions(${target} PRIVATE TRINAMIC_ENABLE=2240 TRINAMIC_UART_ENABLE=1 TMC_UART=1 TRINAMIC_I2C=0 TRINAMIC_MIXED_DRIVERS=0 EEPROM_ENABLE=128 EEPROM_IS_FRAM=1 NVS_SIZE=8192 NVS_SIZE_MAX=16384)
endforeach()

set_tests_properties(plugin_trinamic.2240_uart_transport PROPERTIES WILL_FAIL TRUE LABELS known_bug)
