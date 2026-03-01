cmake_minimum_required(VERSION 3.30)
project(DeviceTest VERSION 0.1 LANGUAGES CXX)

# 设置 C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 自动化处理：MOC, UIC, RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 寻找 Qt 组件
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ==========================================
# 引入组件模块目录
# ==========================================
add_subdirectory(modules/Comm)

# 主程序源文件
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# 创建可执行文件
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DeviceTest MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    add_executable(DeviceTest ${PROJECT_SOURCES})
endif()

# ==========================================
# 链接组件库 (核心步骤)
# ==========================================
target_link_libraries(DeviceTest PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Comm    # 此处链接我们在子目录定义的库
)