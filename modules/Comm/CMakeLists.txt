add_library(Comm STATIC
    src/TreeView.cpp
    include/Comm/TreeView.h
)

target_link_libraries(Comm PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# ==========================================
# 关键设置：外界可以直接使用包含目录，无需繁琐路径
# ==========================================
target_include_directories(Comm PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
