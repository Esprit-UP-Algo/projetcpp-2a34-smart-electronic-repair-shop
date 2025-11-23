cmake_minimum_required(VERSION 3.16)
project(sans_titre1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver Qt (Qt5 ou Qt6)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Charts PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts PrintSupport)

# Fichiers du projet
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    employe.cpp
    connexion.cpp
    mailingservice.cpp
    qrcode.cpp

    mainwindow.h
    employe.h
    connexion.h
    mailingservice.h
    qrcode.h

    mainwindow.ui
)

# Création de l'exécutable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(sans_titre1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(sans_titre1
        ${PROJECT_SOURCES}
    )
endif()

# Lier les modules Qt
target_link_libraries(sans_titre1 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

# Propriétés macOS / Windows
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.sans_titre1)
endif()

set_target_properties(sans_titre1 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installation
include(GNUInstallDirs)
install(TARGETS sans_titre1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalisation Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(sans_titre1)
endif()
