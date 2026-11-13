cmake_minimum_required(VERSION 3.16)

include("${CMAKE_CURRENT_LIST_DIR}/cmake/OpenVUtils.cmake")
openv_extract_version()

if(OPENV_ROCKCHIP_DIR)
    set(CMAKE_TOOLCHAIN_FILE "${OPENV_ROCKCHIP_DIR}/share/buildroot/toolchainfile.cmake" CACHE FILEPATH "" FORCE)
endif()

project(OpenV VERSION ${OPENV_VERSION} LANGUAGES CXX)
message(STATUS "Build openv:" ${OPENV_VERSION})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
    endif()
endif()

# if(DEFINED OPENV_ROCKCHIP_DIR AND NOT CMAKE_CXX_FLAGS MATCHES "-march=armv8-a")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a")
# endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/OpenV" CACHE PATH "" FORCE)
endif()

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()
    
if(WIN32)
    add_compile_definitions(OPENV_BUILD)
endif()

if(MSVC)
    add_compile_options(/utf-8)
endif()

set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_INLINES_HIDDEN ON)

option(OPENV_BUILD_PLUGIN_VCAM "OpenV Plugin VCAM Support" ON)
option(OPENV_BUILD_PLUGIN_VDEC "OpenV Plugin VDEC Support" ON)
option(OPENV_BUILD_PLUGIN_VENC "OpenV Plugin VENC Support" ON)
option(OPENV_BUILD_PLUGIN_VGFX "OpenV Plugin VGFX Support" ON)
option(OPENV_BUILD_PLUGIN_VMUX "OpenV Plugin VMUX Support" ON)
option(OPENV_BUILD_PLUGIN_VPSS "OpenV Plugin VPSS Support" ON)
option(OPENV_BUILD_PLUGIN_VWIN "OpenV Plugin VWIN Support" ON)
option(OPENV_BUILD_PLUGIN_TEST "OpenV Plugin TEST Support" ON)

add_subdirectory(src/base)
add_subdirectory(src/core)

if(OPENV_BUILD_PLUGIN_VCAM)
    add_subdirectory(src/plugin/vcam)
endif()

if(OPENV_BUILD_PLUGIN_VDEC)
    add_subdirectory(src/plugin/vdec)
endif()

if(OPENV_BUILD_PLUGIN_VENC)
    add_subdirectory(src/plugin/venc)
endif()

if(OPENV_BUILD_PLUGIN_VGFX)
    add_subdirectory(src/plugin/vgfx)
endif()

if(OPENV_BUILD_PLUGIN_VMUX)
    add_subdirectory(src/plugin/vmux)
endif()

if(OPENV_BUILD_PLUGIN_VPSS)
    add_subdirectory(src/plugin/vpss)
endif()

if(OPENV_BUILD_PLUGIN_VWIN)
    add_subdirectory(src/plugin/vwin)
endif()

if(OPENV_BUILD_PLUGIN_TEST)
    add_subdirectory(test)
endif()

install(EXPORT OpenVTargets
    FILE      OpenVTargets.cmake
    NAMESPACE OpenV::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OpenV"
    COMPONENT devel
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/OpenVConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/OpenVConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OpenV"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/OpenVConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/OpenVConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/OpenVConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OpenV"
    COMPONENT devel
)
