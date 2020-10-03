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
# Test Libraries
# ====================================================
add_library(lib_test_crc STATIC
  test_chimera_crc.cpp
  chimera_crc_backend.cpp
)
target_link_libraries(lib_test_crc PRIVATE ${LINK_LIBS})
target_include_directories(lib_test_crc PRIVATE ".")
export(TARGETS lib_test_crc FILE "${PROJECT_BINARY_DIR}/tests/src/peripherals/lib_test_crc.cmake")