cmake_minimum_required(VERSION 3.20)
project(grblhal_encoder_tests LANGUAGES C)
include(../../components.cmake)
foreach(behavior defaults feed_counts universal_modes rapid_extra_low rapid_return_low settings_values allocation_failure owned_encoder persist_write persist_read multiple_encoders skip_spindle)
  component_case(plugin_encoder.${behavior} ${behavior}.c encoder_host.c
    "${HARNESS_ROOT}/plugins/encoder/encoder.c" "${COMPONENT_CORE_ROOT}/encoders.c"
    "${HARNESS_ROOT}/plugins/eeprom/eeprom_24AAxxx.c" "${HARNESS_ROOT}/tests/plugins/eeprom/eeprom_host.c"
    "${COMPONENT_CORE_ROOT}/crc.c" "${COMPONENT_CORE_ROOT}/nuts_bolts.c")
  target_include_directories(plugin_encoder.${behavior} PRIVATE "${HARNESS_ROOT}/tests/plugins/eeprom" "${HARNESS_ROOT}/plugins/eeprom")
  target_compile_definitions(plugin_encoder.${behavior} PRIVATE ENCODER_ENABLE=1 EEPROM_ENABLE=128 EEPROM_IS_FRAM=1 NVS_SIZE=8192 NVS_SIZE_MAX=16384)
  if(behavior STREQUAL "multiple_encoders" OR behavior STREQUAL "skip_spindle")
    target_compile_definitions(plugin_encoder.${behavior} PRIVATE QEI_ENABLE=2)
  else()
    target_compile_definitions(plugin_encoder.${behavior} PRIVATE QEI_ENABLE=1)
  endif()
endforeach()
# As in the main harness's CORE build, retain production warnings without promoting them; fixtures remain strict.
set_source_files_properties("${HARNESS_ROOT}/plugins/encoder/encoder.c" PROPERTIES COMPILE_OPTIONS -Wno-error)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/encoder-persistent")
set_tests_properties(plugin_encoder.persist_write PROPERTIES FIXTURES_SETUP encoder_nvs)
set_tests_properties(plugin_encoder.persist_read PROPERTIES FIXTURES_REQUIRED encoder_nvs)
set_tests_properties(plugin_encoder.persist_write plugin_encoder.persist_read PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/encoder-persistent")

set_tests_properties(plugin_encoder.rapid_extra_low plugin_encoder.rapid_return_low plugin_encoder.multiple_encoders plugin_encoder.skip_spindle PROPERTIES WILL_FAIL TRUE LABELS known_bug)
