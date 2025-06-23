cmake_minimum_required(VERSION 3.6.0)

project(simple_3d_viewer VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets Gui REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(PROJECT_SOURCES
    main.cc main.h
    view.cc view.h mainwindow.ui
    view/glview.cc view/glview.h
    ctrl_c/controller.h ctrl_c/controller.cc
)

add_executable(simple_3d_viewer ${PROJECT_SOURCES})

# Добавляем поддиректорию с giflib
add_subdirectory(3rdparty/giflib)

# Подключаем giflib к нашему проекту
#target_include_directories(simple_3d_viewer PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/giflib)
target_link_libraries(simple_3d_viewer PRIVATE giflib)

set(OBJECT_LIB_PATH "${CMAKE_SOURCE_DIR}/resources/object.a")
target_link_libraries(simple_3d_viewer PRIVATE ${OBJECT_LIB_PATH})

if(WIN32)
    target_link_libraries(simple_3d_viewer PRIVATE Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets Qt6::Gui opengl32 glu32)
elseif(APPLE)
    target_link_libraries(simple_3d_viewer PRIVATE Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets Qt6::Gui)
elseif(UNIX)
    target_link_libraries(simple_3d_viewer PRIVATE Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets Qt6::Gui GL)
endif()

if(APPLE)
    set_target_properties(simple_3d_viewer PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
    )
elseif(WIN32)
    set_target_properties(simple_3d_viewer PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Финализация Qt для версии 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(simple_3d_viewer)
endif()
