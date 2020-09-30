set(TARGET_CHIP prj_device_target)
add_library(${TARGET_CHIP} INTERFACE)
target_compile_options(${TARGET_CHIP} INTERFACE
  # -fdata-sections
  # -ffunction-sections
  # -fmessage-length=0
  # -fno-common
  # -fno-exceptions
  -m64
  $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
)

target_link_options(${TARGET_CHIP} INTERFACE
  # -Wl,--gc-sections
)

target_compile_definitions(${TARGET_CHIP} INTERFACE
  CHIMERA_LITTLE_ENDIAN
)

export(TARGETS ${TARGET_CHIP} FILE "${PROJECT_BINARY_DIR}/DeviceTarget/${TARGET_CHIP}.cmake")


add_executable(system_tests "tests/test_runner.cpp")
target_link_libraries(system_tests PRIVATE
  # Public Includes
  gtest_inc
  chimera_inc
  aurora_inc
  Boost::boost
  type_safe_inc
  prj_device_target

  # Static Libraries
  -Wl,--whole-archive
  gtest_src
  chimera_src
  chimera_src_tests
  -Wl,--no-whole-archive
)
export(TARGETS system_tests FILE "${PROJECT_BINARY_DIR}/tests/system_tests.cmake")