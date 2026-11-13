add_library(base)
add_library(OpenV::base ALIAS base)

target_sources(base
    PRIVATE
        ovDir.cpp
        ovLibrary.cpp
        ovEnvironment.cpp
        ovPluginLoader.cpp
)

target_include_directories(base 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/base> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(WIN32)
    target_link_libraries(base PRIVATE ws2_32)
endif()

set_target_properties(base PROPERTIES
    OUTPUT_NAME "openv_base"
)

install(TARGETS base
    EXPORT OpenVTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set(OPENV_HEADERS
    "${PROJECT_SOURCE_DIR}/include/openv/openv.h"
    "${PROJECT_SOURCE_DIR}/include/openv/openv.hpp"
)

set(OPENV_BASE_HEADERS
    "${PROJECT_SOURCE_DIR}/include/openv/base/ovDir.h"
    "${PROJECT_SOURCE_DIR}/include/openv/base/ovFlags.h"
    "${PROJECT_SOURCE_DIR}/include/openv/base/ovPlugin.h"
    "${PROJECT_SOURCE_DIR}/include/openv/base/ovLibrary.h"
    "${PROJECT_SOURCE_DIR}/include/openv/base/ovEnvironment.h"
    "${PROJECT_SOURCE_DIR}/include/openv/base/ovPluginLoader.h"
)

install(FILES ${OPENV_HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/openv")
install(FILES ${OPENV_BASE_HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/openv/base")
