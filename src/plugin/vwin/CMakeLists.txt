add_library(vwin)
add_library(OpenV::vwin ALIAS vwin)

target_sources(vwin
    PRIVATE
        ovWindow.cpp
)

target_include_directories(vwin 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/plugin/vwin> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/core> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/base>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(vwin PRIVATE OpenV::base OpenV::core)

set_target_properties(vwin PROPERTIES
    OUTPUT_NAME "openv_vwin"
)

openv_install_module(vwin)