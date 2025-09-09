cmake_minimum_required(VERSION 3.16)

project(HighNoon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick LinguistTools)

set(TS_FILES TestQtAndroid_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HighNoon
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        TimerLogic.h
        Level.cpp
        timer.h timer.cpp
        Sounds.h
        Hero.cpp
        Images/Images.qrc
        GameLogic.cpp
        Enemy.cpp
        Weapon.cpp
        Hero.h
        Weapon.h
        Pause.h
        Pause.cpp
        WindWitch.h
        WindWitch.cpp
        Enemy.h
        Shop.h
        Shop.cpp
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(HighNoon SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(HighNoon
          ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(HighNoon
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.HighNoon)
endif()
set_target_properties(HighNoon PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS HighNoon
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(HighNoon)
    qt_finalize_executable(HighNoon)
endif()  # закрываем именно QT_VERSION_MAJOR EQUAL 6
