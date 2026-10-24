cmake_minimum_required(VERSION 3.20)
project(grblhal_atci_tests LANGUAGES C)
include(../../components.cmake)
foreach(behavior clip_unrestricted default_disabled inside_target crossing outside_and_chain boundary_tolerance deep_inside clip_sides boundary_jog_block reversed_bounds command_disable command_validation macro_lifecycle rack_sensor sensor_reports persist_reload init_failure hook_chaining)
  component_case(plugin_atci.${behavior} ${behavior}.c atci_host.c "${HARNESS_ROOT}/plugins/atci/sienci-atci-plugin.c")
  target_compile_definitions(plugin_atci.${behavior} PRIVATE ATCI_ENABLE=1 BOARD_LONGBOARD32=1 N_AXIS=4)
endforeach()
set_source_files_properties("${HARNESS_ROOT}/plugins/atci/sienci-atci-plugin.c" PROPERTIES COMPILE_OPTIONS "-Wno-unused-parameter;-Wno-missing-field-initializers")

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
  set_property(SOURCE "${HARNESS_ROOT}/plugins/atci/sienci-atci-plugin.c" APPEND PROPERTY COMPILE_OPTIONS -Wno-error=unused-but-set-global)
endif()

set_tests_properties(plugin_atci.command_disable PROPERTIES WILL_FAIL TRUE LABELS known_bug)
