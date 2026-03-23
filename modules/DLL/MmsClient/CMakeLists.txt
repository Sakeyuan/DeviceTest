cmake_minimum_required(VERSION 3.10)
project(MmsClient)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect source files
set(SOURCES
    src/client.c
    src/cli_rpt.c
    src/clntobj.c
    src/event.c
    src/interface.c
    src/mmsop_en.c
    src/mvlop_en.c
    src/mvl_acse.c
    src/reject.c
)

# Collect header files
set(HEADERS
    src/client.h
    src/clntobj.h
    src/interface.h
    src/mmsop_en.h
)

add_library(MmsClient STATIC ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(MmsClient PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>)

# Platform-specific settings
if(WIN32)
    # Windows-specific includes or libraries if needed
    target_compile_definitions(MmsClient PRIVATE _WINDOWS MMS_LITE)
    target_link_libraries(MmsClient PRIVATE ws2_32)
endif()

# Set output directory
set_target_properties(MmsClient PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)