file(GLOB_RECURSE SRC_FILES
    "src/*.cpp"
    "src/*.h"
    "include/*.h"
    "3rdparty/pugixml/src/*.cpp"
    "3rdparty/pugixml/src/*.hpp"
    "3rdparty/pugixml/src/*.h"
)

add_library(ScdParse STATIC ${SRC_FILES})

target_include_directories(ScdParse PUBLIC

    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/pugixml/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

