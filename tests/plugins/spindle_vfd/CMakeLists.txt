cmake_minimum_required(VERSION 3.20)
project(grblhal_vfd_tests LANGUAGES C)
include(../../components.cmake)
foreach(protocol gs20 modvfd)
  set(behaviors commands feedback update_rpm mode_rejected async_exceptions exception_reset cold_exception settings_hooks no_transport no_storage bus_down persist_write persist_read)
  if(protocol STREQUAL "gs20")
    set(mask 8)
    set(custom configured_hz)
    set(is_mod 0)
  else()
    set(mask 32)
    set(custom configured_registers)
    set(is_mod 1)
  endif()
  foreach(behavior ${behaviors} ${custom})
    component_case(plugin_spindle_vfd.${protocol}_${behavior} ${behavior}.c vfd_host.c
      "${HARNESS_ROOT}/plugins/spindle/vfd/${protocol}.c" "${HARNESS_ROOT}/plugins/spindle/vfd/spindle.c"
      "${COMPONENT_CORE_ROOT}/spindle_control.c" "${COMPONENT_CORE_ROOT}/modbus.c"
      "${HARNESS_ROOT}/plugins/eeprom/eeprom_24AAxxx.c" "${HARNESS_ROOT}/tests/plugins/eeprom/eeprom_host.c"
      "${COMPONENT_CORE_ROOT}/crc.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c")
    target_include_directories(plugin_spindle_vfd.${protocol}_${behavior} PRIVATE "${HARNESS_ROOT}/plugins" "${HARNESS_ROOT}/tests/plugins/eeprom" "${HARNESS_ROOT}/plugins/eeprom")
    target_compile_definitions(plugin_spindle_vfd.${protocol}_${behavior} PRIVATE SPINDLE_ENABLE=${mask} VFD_ENABLE=1 TEST_MODVFD=${is_mod} EEPROM_ENABLE=128 EEPROM_IS_FRAM=1 NVS_SIZE=8192 NVS_SIZE_MAX=16384)
  endforeach()
  file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${protocol}-persistent")
  set_tests_properties(plugin_spindle_vfd.${protocol}_persist_write PROPERTIES FIXTURES_SETUP ${protocol}_nvs)
  set_tests_properties(plugin_spindle_vfd.${protocol}_persist_read PROPERTIES FIXTURES_REQUIRED ${protocol}_nvs)
  set_tests_properties(plugin_spindle_vfd.${protocol}_persist_write plugin_spindle_vfd.${protocol}_persist_read PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${protocol}-persistent")
endforeach()
set_source_files_properties("${HARNESS_ROOT}/plugins/spindle/vfd/gs20.c" "${HARNESS_ROOT}/plugins/spindle/vfd/modvfd.c" "${HARNESS_ROOT}/plugins/spindle/vfd/spindle.c" "${COMPONENT_CORE_ROOT}/spindle_control.c" PROPERTIES COMPILE_OPTIONS -Wno-error)
set_source_files_properties("${COMPONENT_CORE_ROOT}/modbus.c" PROPERTIES COMPILE_OPTIONS -Wno-error)

foreach(behavior discovery commands feedback limits retry reset four_poles no_transport no_storage)
  if(behavior MATCHES "^no_")
    set(test_source ${behavior}.c)
  else()
    set(test_source h100_${behavior}.c)
  endif()
  set(target plugin_spindle_vfd.h100_${behavior})
  component_case(${target} ${test_source} vfd_host.c
    "${HARNESS_ROOT}/plugins/spindle/vfd/h100.c" "${HARNESS_ROOT}/plugins/spindle/vfd/spindle.c"
    "${COMPONENT_CORE_ROOT}/spindle_control.c" "${COMPONENT_CORE_ROOT}/modbus.c"
    "${HARNESS_ROOT}/plugins/eeprom/eeprom_24AAxxx.c" "${HARNESS_ROOT}/tests/plugins/eeprom/eeprom_host.c"
    "${COMPONENT_CORE_ROOT}/crc.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c")
  target_include_directories(${target} PRIVATE "${HARNESS_ROOT}/plugins" "${HARNESS_ROOT}/tests/plugins/eeprom" "${HARNESS_ROOT}/plugins/eeprom")
  target_compile_definitions(${target} PRIVATE SPINDLE_ENABLE=64 VFD_ENABLE=1 TEST_H100=1 TEST_MODVFD=0 EEPROM_ENABLE=128 EEPROM_IS_FRAM=1 NVS_SIZE=8192 NVS_SIZE_MAX=16384)
endforeach()
set_source_files_properties("${HARNESS_ROOT}/plugins/spindle/vfd/h100.c" PROPERTIES COMPILE_OPTIONS -Wno-error)

foreach(behavior commands feedback configured_hz update_rpm mode_rejected async_exceptions exception_reset settings_hooks no_transport no_storage bus_down)
  if(behavior MATCHES "^(commands|feedback|configured_hz|update_rpm)$")
    set(test_source yl620_${behavior}.c)
  else()
    set(test_source ${behavior}.c)
  endif()
  set(target plugin_spindle_vfd.yl620_${behavior})
  component_case(${target} ${test_source} vfd_host.c
    "${HARNESS_ROOT}/plugins/spindle/vfd/yl620.c" "${HARNESS_ROOT}/plugins/spindle/vfd/spindle.c"
    "${COMPONENT_CORE_ROOT}/spindle_control.c" "${COMPONENT_CORE_ROOT}/modbus.c"
    "${HARNESS_ROOT}/plugins/eeprom/eeprom_24AAxxx.c" "${HARNESS_ROOT}/tests/plugins/eeprom/eeprom_host.c"
    "${COMPONENT_CORE_ROOT}/crc.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c")
  target_include_directories(${target} PRIVATE "${HARNESS_ROOT}/plugins" "${HARNESS_ROOT}/tests/plugins/eeprom" "${HARNESS_ROOT}/plugins/eeprom")
  target_compile_definitions(${target} PRIVATE SPINDLE_ENABLE=16 VFD_ENABLE=1 TEST_MODVFD=0 EEPROM_ENABLE=128 EEPROM_IS_FRAM=1 NVS_SIZE=8192 NVS_SIZE_MAX=16384)
endforeach()
set_source_files_properties("${HARNESS_ROOT}/plugins/spindle/vfd/yl620.c" PROPERTIES COMPILE_OPTIONS -Wno-error)

foreach(behavior commands feedback reset retry async_exceptions exception_reset settings_hooks no_transport no_storage bus_down)
  if(behavior MATCHES "^(commands|feedback|reset|retry)$")
    set(test_source huanyang2_${behavior}.c)
  else()
    set(test_source ${behavior}.c)
  endif()
  set(target plugin_spindle_vfd.huanyang2_${behavior})
  component_case(${target} ${test_source} vfd_host.c
    "${HARNESS_ROOT}/plugins/spindle/vfd/huanyang2.c" "${HARNESS_ROOT}/plugins/spindle/vfd/spindle.c"
    "${COMPONENT_CORE_ROOT}/spindle_control.c" "${COMPONENT_CORE_ROOT}/modbus.c"
    "${HARNESS_ROOT}/plugins/eeprom/eeprom_24AAxxx.c" "${HARNESS_ROOT}/tests/plugins/eeprom/eeprom_host.c"
    "${COMPONENT_CORE_ROOT}/crc.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c")
  target_include_directories(${target} PRIVATE "${HARNESS_ROOT}/plugins" "${HARNESS_ROOT}/tests/plugins/eeprom" "${HARNESS_ROOT}/plugins/eeprom")
  target_compile_definitions(${target} PRIVATE SPINDLE_ENABLE=4 VFD_ENABLE=1 TEST_HUANYANG2=1 TEST_MODVFD=0 EEPROM_ENABLE=128 EEPROM_IS_FRAM=1 NVS_SIZE=8192 NVS_SIZE_MAX=16384)
endforeach()
set_source_files_properties("${HARNESS_ROOT}/plugins/spindle/vfd/huanyang2.c" PROPERTIES COMPILE_OPTIONS -Wno-error)
