# ====================================================
# Common
# ====================================================
set(LINK_LIBS
  aurora_inc        # Aurora public headers
  Boost::boost      # Boost public headers
  chimera_inc       # Chimera public headers
  gtest_inc         # Google test public headers
  prj_device_target # Compiler options for target device
)

# ====================================================
# Additional Projects
# ====================================================
add_subdirectory("peripherals/can")
add_subdirectory("peripherals/clock")
add_subdirectory("peripherals/crc")
add_subdirectory("peripherals/dma")
add_subdirectory("peripherals/gpio")
add_subdirectory("peripherals/power")
add_subdirectory("peripherals/spi")
add_subdirectory("peripherals/timer")
add_subdirectory("peripherals/uart")
add_subdirectory("peripherals/usart")
add_subdirectory("peripherals/watchdog")
add_subdirectory("threading")

# ====================================================
# Test Libraries
# ====================================================

# BUFFER
add_library(lib_test_buffer STATIC
  buffer/test_buffer.cpp
)
target_link_libraries(lib_test_buffer PRIVATE ${LINK_LIBS})
export(TARGETS lib_test_buffer FILE "${PROJECT_BINARY_DIR}/tests/src/lib_test_buffer.cmake")

# CONTAINER
add_library(lib_test_container STATIC
  container/test_container.cpp
)
target_link_libraries(lib_test_container PRIVATE ${LINK_LIBS})
export(TARGETS lib_test_container FILE "${PROJECT_BINARY_DIR}/tests/src/lib_test_container.cmake")