add_executable(test_helper
    ../../helper.h
    main.cpp
)

include(GNUInstallDirs)
install(TARGETS test_helper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
