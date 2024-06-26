cmake_minimum_required(VERSION 3.5)

project(Backie VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)


set(TASKSCHED_LIB "${CMAKE_CURRENT_SOURCE_DIR}/taskschd.lib")


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
        backupscreen.h backupscreen.cpp backupscreen.ui
        signinscreen.h signinscreen.cpp signinscreen.ui
        recoveryscreen.h recoveryscreen.cpp recoveryscreen.ui
        Resources.qrc
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Backie
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        settings.h settings.cpp


        backupscreen.h backupscreen.cpp backupscreen.ui
        signinscreen.h signinscreen.cpp signinscreen.ui
        assets/icons/licenses/delete
        recoveryscreen.h recoveryscreen.cpp recoveryscreen.ui
        styles/global.css
        assets/icons/sideBar/active/backup_grey.svg assets/icons/sideBar/active/history_grey.svg assets/icons/sideBar/active/home_grey.svg assets/icons/sideBar/active/recover_grey.svg assets/icons/sideBar/active/settings_grey.svg assets/icons/sideBar/iconLicenses/license-56530056-3916611.pdf assets/icons/sideBar/iconLicenses/license-56530056-3917033.pdf assets/icons/sideBar/iconLicenses/license-56530056-3917058.pdf assets/icons/sideBar/iconLicenses/license-56530056-3917296.pdf assets/icons/sideBar/iconLicenses/license-56530056-3917330.pdf assets/icons/sideBar/iconLicenses/license-56530056-3917688.pdf assets/icons/sideBar/notActive/account_white.svg assets/icons/sideBar/notActive/backup_white.svg assets/icons/sideBar/notActive/history_white.svg assets/icons/sideBar/notActive/home_white.svg assets/icons/sideBar/notActive/recover_white.svg assets/icons/sideBar/notActive/settings_white.svg
        styles/backupScreen.css

        errand.h errand.cpp


        utils.h utils.cpp
        dialogcalendar.h dialogcalendar.cpp dialogcalendar.ui
        metadata.h
        metadata.cpp
        destination.h destination.cpp


        backupbuilder.h backupbuilder.cpp
        schedule.h schedule.cpp
        task.h task.cpp
        assets/fonts/Roboto/Roboto-Bold.ttf assets/fonts/Roboto/Roboto-Italic.ttf assets/fonts/Roboto/Roboto-Medium.ttf assets/fonts/Roboto/Roboto-MediumItalic.ttf assets/fonts/Roboto/Roboto-Regular.ttf
        welcomebackupscreen.h welcomebackupscreen.cpp welcomebackupscreen.ui
        assets/icons/main/plus_icon.svg
        taskcard.h taskcard.cpp taskcard.ui
        styles/taskCard.css

    )
# Define target properties for An
#    set_property(TARGET Backie APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Backie SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Backie
            ${PROJECT_SOURCES}
        )
    endif()
endif()


add_subdirectory(spdlog)

target_link_libraries(Backie PRIVATE
   Qt6::Network
   Qt${QT_VERSION_MAJOR}::Widgets
   ${TASKSCHED_LIB}
   spdlog::spdlog)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Backie)
endif()
set_target_properties(Backie PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Backie
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Backie)
endif()
