find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(test_qhelper
    ../../helper.h
    ../../qhelper.h
    main.cpp
)

qt_add_qml_module(test_qhelper
    URI test_qhelper
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(test_qhelper PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(test_qhelper
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS test_qhelper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
