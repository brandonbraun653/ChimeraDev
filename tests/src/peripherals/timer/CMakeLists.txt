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
add_library(lib_test_timer STATIC
  test_chimera_timer.cpp
  chimera_timer_backend.cpp
)
target_link_libraries(lib_test_timer PRIVATE ${LINK_LIBS})
target_include_directories(lib_test_timer PRIVATE ".")
export(TARGETS lib_test_timer FILE "${PROJECT_BINARY_DIR}/tests/src/peripherals/lib_test_timer.cmake")