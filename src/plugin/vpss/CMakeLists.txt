add_library(vpss)
add_library(OpenV::vpss ALIAS vpss)

target_sources(vpss
    PRIVATE
        ovProcessor.cpp
)

target_include_directories(vpss 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/plugin/vpss> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/core> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/base>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(vpss PRIVATE OpenV::base OpenV::core)

set_target_properties(vpss PROPERTIES
    OUTPUT_NAME "openv_vpss"
)

openv_install_module(vpss)