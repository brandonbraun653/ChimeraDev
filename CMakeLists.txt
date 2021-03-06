cmake_minimum_required(VERSION 3.18.0)
project(ThorDev VERSION 0.1.0)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# ====================================================
# Perform very high level configuration
# ====================================================
# Set some vars common to both development environments
include("lib/CommonTools/cmake/options/common.cmake")

# Override the linker command
include("lib/CommonTools/cmake/toolchains/linker_whole_archive.cmake")

# ====================================================
# Import common packages and projects
# ====================================================
find_package(Boost REQUIRED)
add_subdirectory("lib/CommonTools/googletest")
add_subdirectory("lib/Aurora")
add_subdirectory("lib/FreeRTOS")
add_subdirectory("Chimera")
add_subdirectory("tests")

# ====================================================
# Import the test driver targets
# ====================================================
include("tests/targets.cmake")