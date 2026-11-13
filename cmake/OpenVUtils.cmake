function(openv_extract_version)
    file(READ "${CMAKE_CURRENT_LIST_DIR}/include/openv/openv.h" file_contents)
    string(REGEX MATCH "OPENV_VERSION_MAJOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number from openv/openv.h")
    endif()
    set(ver_major ${CMAKE_MATCH_1})

    string(REGEX MATCH "OPENV_VERSION_MINOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract minor version number from openv/openv.h")
    endif()

    set(ver_minor ${CMAKE_MATCH_1})
    string(REGEX MATCH "OPENV_VERSION_PATCH ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract patch version number from openv/openv.h")
    endif()
    set(ver_patch ${CMAKE_MATCH_1})

    set(OPENV_VERSION_MAJOR ${ver_major} PARENT_SCOPE)
    set(OPENV_VERSION_MINOR ${ver_minor} PARENT_SCOPE)
    set(OPENV_VERSION_PATCH ${ver_patch} PARENT_SCOPE)
    set(OPENV_VERSION "${ver_major}.${ver_minor}.${ver_patch}" PARENT_SCOPE)
endfunction()

function(openv_install_module TARGET)
    set_target_properties(${TARGET} PROPERTIES INSTALL_RPATH "$ORIGIN" BUILD_RPATH "$ORIGIN")

    install(TARGETS ${TARGET}
        EXPORT    OpenVTargets
        RUNTIME   DESTINATION ${CMAKE_INSTALL_BINDIR}   COMPONENT ${TARGET}
        LIBRARY   DESTINATION ${CMAKE_INSTALL_LIBDIR}   COMPONENT ${TARGET}
        ARCHIVE   DESTINATION ${CMAKE_INSTALL_LIBDIR}   COMPONENT ${TARGET}
        INCLUDES  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/openv/plugin/${TARGET}"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/openv"
            COMPONENT ${TARGET}
            FILES_MATCHING PATTERN "*.h")
endfunction()