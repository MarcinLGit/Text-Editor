find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(TS_FILES ZPR_pl_PL.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ZPR
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(ZPR PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ZPR PROPERTIES
    ${BUNDLE_ID_OPTION}

    WIN32_EXECUTABLE TRUE
)


include(GNUInstallDirs)
install(TARGETS ZPR
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ZPR)
endif()

add_subdirectory(lib)
