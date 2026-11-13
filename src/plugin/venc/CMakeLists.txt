add_library(venc)
add_library(OpenV::venc ALIAS venc)

target_sources(venc
    PRIVATE
        ovEncoder.cpp
)

target_include_directories(venc 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/plugin/venc> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/core> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/base>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(venc PRIVATE OpenV::base OpenV::core)

set_target_properties(venc PROPERTIES
    OUTPUT_NAME "openv_venc"
)

openv_install_module(venc)