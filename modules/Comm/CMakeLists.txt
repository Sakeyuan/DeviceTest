file(GLOB SRC_FILES
    "src/*.cpp"
    "include/Comm/*.h"
)

add_library(Comm STATIC ${SRC_FILES})

target_include_directories(Comm PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/spdlog/include>
)

target_link_libraries(Comm PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Threads::Threads
)
