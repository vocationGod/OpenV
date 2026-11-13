add_library(vgfx)
add_library(OpenV::vgfx ALIAS vgfx)

target_sources(vgfx
    PRIVATE
        ovPen.cpp
        ovFont.cpp
        ovBrush.cpp
        ovColor.cpp
        ovPainter.cpp
)

target_include_directories(vgfx 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/plugin/vgfx> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/core> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv/base>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/openv> 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(vgfx PRIVATE OpenV::base OpenV::core)

target_compile_definitions(vgfx PUBLIC HAVE_OPENV_PLUGIN_VGFX)

set_target_properties(vgfx PROPERTIES
    OUTPUT_NAME "openv_vgfx"
)

openv_install_module(vgfx)