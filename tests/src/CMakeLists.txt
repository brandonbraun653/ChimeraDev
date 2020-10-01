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
add_subdirectory("peripherals/gpio")

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