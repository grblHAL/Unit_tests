cmake_minimum_required(VERSION 3.20)
project(grblhal_misc_tests LANGUAGES C)
include(../../components.cmake)
foreach(behavior validation execution chaining)
  component_case(plugins_misc.m220_${behavior} m220_${behavior}.c misc_host.c m220_init.c "${HARNESS_ROOT}/core/nuts_bolts.c" "${HARNESS_ROOT}/plugins/misc/feed_override_m220.c")
  target_compile_definitions(plugins_misc.m220_${behavior} PRIVATE FEED_OVERRIDE_ENABLE=1)
endforeach()

foreach(behavior validation strip_output masked_output no_driver)
  component_case(plugins_misc.m150_${behavior} m150_${behavior}.c rgb_host.c misc_host.c "${HARNESS_ROOT}/core/nuts_bolts.c" "${HARNESS_ROOT}/plugins/misc/rgb_led_m150.c")
  target_compile_definitions(plugins_misc.m150_${behavior} PRIVATE RGB_LED_ENABLE=2)
endforeach()
foreach(behavior attach_and_move failed_attach validation_and_readback)
  component_case(plugins_misc.m280_${behavior} m280_${behavior}.c servo_host.c misc_host.c "${HARNESS_ROOT}/core/nuts_bolts.c" "${HARNESS_ROOT}/plugins/misc/pwm_servo_m280.c")
  target_compile_definitions(plugins_misc.m280_${behavior} PRIVATE PWM_SERVO_ENABLE=1 N_PWM_SERVOS=2)
endforeach()

# Upstream servo callback intentionally leaves its opaque context unused.
set_source_files_properties("${HARNESS_ROOT}/plugins/misc/pwm_servo_m280.c" PROPERTIES COMPILE_OPTIONS -Wno-unused-parameter)
