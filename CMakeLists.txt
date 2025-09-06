cmake_minimum_required(VERSION 3.20)
project(R3
    VERSION 1.0.0
    DESCRIPTION "Modern C++ header-only library"
    HOMEPAGE_URL "https://github.com/pooriayousefi/R3"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header-only library target
add_library(R3 INTERFACE)
target_include_directories(R3 INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Set interface properties
target_compile_features(R3 INTERFACE cxx_std_20)

# Platform-specific compile definitions
if(WIN32)
    target_compile_definitions(R3 INTERFACE _WIN32_WINNT=0x0601)
endif()

# Installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS R3
    EXPORT R3Targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/R3.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    OPTIONAL
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/R3.ixx
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    OPTIONAL
)

# Export targets
install(EXPORT R3Targets
    FILE R3Targets.cmake
    NAMESPACE R3::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/R3
)

# Create package config
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/R3Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/R3Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/R3
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/R3ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/R3Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/R3ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/R3
)

# Configuration summary
message(STATUS "R3 Configuration Summary:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Platform: ${CMAKE_SYSTEM_NAME}")
