# ====================================================
# Add subdirectories containing tests
# ====================================================
add_subdirectory("src")

# ====================================================
# All test drivers
# ====================================================
add_library(chimera_src_tests INTERFACE)
target_link_libraries(chimera_src_tests INTERFACE
  lib_test_buffer
  lib_test_container
  lib_test_gpio
  lib_test_spi
  lib_test_uart
  lib_test_usart
  lib_test_watchdog
)
export(TARGETS chimera_src_tests FILE "${PROJECT_BINARY_DIR}/tests/chimera_src_tests.cmake")