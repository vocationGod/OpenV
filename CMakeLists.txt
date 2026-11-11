cmake_minimum_required(VERSION 3.16)

include("cmake/OpenVUtils.cmake")
openv_version()

project(OpenV VERSION ${OPENV_VERSION} LANGUAGES C CXX)

if(WIN32)
    add_compile_definitions(OPENV_BUILD)
endif()

if(MSVC)
    add_compile_options(/utf-8)
endif()