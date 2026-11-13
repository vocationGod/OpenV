add_library(core)
add_library(OpenV::core ALIAS core)

target_sources(core
    PRIVATE
        ovImage.cpp
        ovSyncer.cpp
        ovElement.cpp
        ovFragment.cpp
)

target_include_directories(core 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/core> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/base>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(core PUBLIC OpenV::base)

set_target_properties(core PROPERTIES
    OUTPUT_NAME "openv_core"
)

install(TARGETS core
    EXPORT OpenVTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set(OPENV_CORE_HEADERS "${PROJECT_SOURCE_DIR}/include/openv/core/ovElement.h")
if(HAVE_OPENV_PLUGIN_VCAM OR HAVE_OPENV_PLUGIN_VENC OR HAVE_OPENV_PLUGIN_VDEC OR HAVE_OPENV_PLUGIN_VWIN OR HAVE_OPENV_PLUGIN_VGFX)
    list(APPEND OPENV_CORE_HEADERS
        "${PROJECT_SOURCE_DIR}/include/openv/core/ovImage.h" 
        "${PROJECT_SOURCE_DIR}/include/openv/core/ovLayout.h"
        "${PROJECT_SOURCE_DIR}/include/openv/core/ovSyncer.h"
    )
endif()

if(HAVE_OPENV_PLUGIN_VENC OR HAVE_OPENV_PLUGIN_VDEC OR HAVE_OPENV_PLUGIN_VMUX)
    list(APPEND OPENV_CORE_HEADERS
        "${PROJECT_SOURCE_DIR}/include/openv/core/ovMedia.h"
        "${PROJECT_SOURCE_DIR}/include/openv/core/ovFragment.h"
    )
endif()

if(OPENV_CORE_HEADERS)
    install(FILES ${OPENV_CORE_HEADERS} DESTINATION DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/openv/core")
endif()