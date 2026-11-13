add_library(vdec)
add_library(OpenV::vdec ALIAS vdec)

target_sources(vdec
    PRIVATE
        ovDecoder.cpp
)

target_include_directories(vdec 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/plugin/vdec> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/core> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/base>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(vdec PRIVATE OpenV::base OpenV::core)

set_target_properties(vdec PROPERTIES
    OUTPUT_NAME "openv_vdec"
)

openv_install_module(vdec)