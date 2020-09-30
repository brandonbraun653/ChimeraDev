# *****************************************************************************
# File Description:
#   Provides many targets useful for running tests on Chimera
#
# 2020 | Brandon Braun | brandonbraun653@gmail.com
# *****************************************************************************

include("${PROJECT_ROOT}/lib/CommonTools/cmake/modules/CodeCoverage.cmake")

# -----------------------------------------------------------------------------
# Project Compiler Options: These will be applied to pretty much every target.
# -----------------------------------------------------------------------------
set(TARGET_CHIP prj_device_target)
add_library(${TARGET_CHIP} INTERFACE)

# Standard Compile/Link Options
target_compile_options(${TARGET_CHIP} INTERFACE
  -fdata-sections
  -ffunction-sections
  -fmessage-length=0
  -fno-common
  -fno-exceptions
  -m64
  $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
)

target_compile_definitions(${TARGET_CHIP} INTERFACE
  CHIMERA_LITTLE_ENDIAN
)

target_link_options(${TARGET_CHIP} INTERFACE
  -Wl,--gc-sections
)

# Enable Coverage Flags
if(COVERAGE)
  target_compile_options(${TARGET_CHIP} INTERFACE --coverage)
  target_link_options(${TARGET_CHIP} INTERFACE --coverage)
endif()

export(TARGETS ${TARGET_CHIP} FILE "${PROJECT_BINARY_DIR}/DeviceTarget/${TARGET_CHIP}.cmake")

# -----------------------------------------------------------------------------
# Primary targets for Chimera testing:
#   system_tests
#   system_tests_coverage
# -----------------------------------------------------------------------------
# Create the executable target
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
  gtest_src
  chimera_src
  chimera_src_tests

  # Linux
  $<$<PLATFORM_ID:Linux>:pthread>
)
export(TARGETS system_tests FILE "${PROJECT_BINARY_DIR}/tests/system_tests.cmake")

# Create the coverage target
setup_target_for_coverage_lcov(
  NAME system_tests_coverage
  EXECUTABLE artifacts/bin/system_tests
  DEPENDENCIES system_tests
  BASE_DIRECTORY "../"
  EXCLUDE "/usr/*" "${PROJECT_ROOT}/tests/*" "${PROJECT_ROOT}/lib/*"
  NO_DEMANGLE
)