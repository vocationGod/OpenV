add_library(vmux)
add_library(OpenV::vmux ALIAS vmux)

target_sources(vmux
    PRIVATE
        ovRTSPServer.cpp
)

target_include_directories(vmux 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/plugin/vmux> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/core> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/base>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(vmux PRIVATE OpenV::base OpenV::core)

set_target_properties(vmux PROPERTIES
    OUTPUT_NAME "openv_vmux"
)

openv_install_module(vmux)