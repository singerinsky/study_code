file(GLOB_RECURSE SRC_LIB_FILES  "*")

add_library(hookstaticlib STATIC ${SRC_LIB_FILES} )

