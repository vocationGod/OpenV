add_library(vcam)
add_library(OpenV::vcam ALIAS vcam)

target_sources(vcam
    PRIVATE
        ovCamera.cpp
)

target_include_directories(vcam 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/plugin/vcam> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/core> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/base>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(vcam PRIVATE OpenV::base OpenV::core)

set_target_properties(vcam PROPERTIES
    OUTPUT_NAME "openv_vcam"
)

openv_install_module(vcam)