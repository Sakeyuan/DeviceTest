set(SCDPARSE_SOURCES
    interface.cpp
    parse.cpp
    strCode.cpp
    tinyxml/tinystr.cpp
    tinyxml/tinyxml.cpp
    tinyxml/tinyxmlerror.cpp
    tinyxml/tinyxmlparser.cpp
)

add_library(ScdParse STATIC ${SCDPARSE_SOURCES})

target_include_directories(ScdParse PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tinyxml>
)
