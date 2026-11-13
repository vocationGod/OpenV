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

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/openv/core" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/openv")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/openv/etcs" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/openv")