set(MMS_SOURCES
    src/client.c src/cli_rpt.c src/clntobj.c src/event.c
    src/interface.c src/mmsop_en.c src/mvlop_en.c
    src/mvl_acse.c src/reject.c
)

add_library(MmsClient STATIC ${MMS_SOURCES})

# 导出 inc 和 src，供外界包含头文件
target_include_directories(MmsClient PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
