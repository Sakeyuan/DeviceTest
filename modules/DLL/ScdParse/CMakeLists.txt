cmake_minimum_required(VERSION 3.10)
project(ScdParse)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ScdParse 库
add_library(ScdParse
    interface.cpp
    parse.cpp
    strCode.cpp
    tinyxml/tinystr.cpp
    tinyxml/tinyxml.cpp
    tinyxml/tinyxmlerror.cpp
    tinyxml/tinyxmlparser.cpp
)

# 包含目录
target_include_directories(ScdParse PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyxml
)

# 定义导出符号（用于 DLL）
if(WIN32)
    target_compile_definitions(ScdParse PRIVATE SCDPARSE_EXPORTS)
endif()

# 禁用安全检查警告（可选）
if(MSVC)
    target_compile_definitions(ScdParse PRIVATE _CRT_SECURE_NO_WARNINGS)
    # 或改为生成 DLL
    # set_target_properties(ScdParse PROPERTIES
    #     WINDOWS_EXPORT_ALL_SYMBOLS ON
    # )
endif()

# ScdTest 可执行程序
add_executable(ScdTest ScdTest/main.cpp)
target_link_libraries(ScdTest ScdParse)
target_include_directories(ScdTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 设置输出目录
set_target_properties(ScdParse ScdTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
