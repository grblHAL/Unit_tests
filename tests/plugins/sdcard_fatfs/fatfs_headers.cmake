# Select the locked FatFs API without pretending the host has an STM32 integer ABI.
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/fatfs/src")
foreach(header ff.h diskio.h)
  file(CONFIGURE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/fatfs/src/${header}"
    CONTENT "#include \"${HARNESS_ROOT}/drivers/stm32f4/FatFs/${header}\"\n" @ONLY)
endforeach()
