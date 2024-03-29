cmake_minimum_required(VERSION 3.5)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)

set(PROJECT_SOURCES
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            Square.h
            Square.cpp
            Game.cpp
            Game.h
            Button.cpp
            Button.h
            Pieces.h
            Pieces.cpp
            data.qrc
            Chessboard.h
            Chessboard.cpp
            Loader.h
            Loader.cpp
            Saver.cpp
            Saver.h
            LanServer.h
            LanClient.h
            LanServer.cpp
            LanClient.cpp
            Window.h
            Window.cpp
            MultiThread.cpp
            MultiThread.h
            Player.h
            Player.cpp
            Timer.cpp
            Timer.h
            DataBaseBridge.cpp
            DataBaseBridge.h
            GameMode.h
            GameMode.cpp
            ComputerPlayer.cpp
            ComputerPlayer.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Chess
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Chess APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Chess SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Chess
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Chess PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Chess PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(Chess PRIVATE Qt6::Network)

install(TARGETS Chess
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Chess)
endif()
