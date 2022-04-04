file(GLOB_RECURSE SRC_LIB_FILES  "*")

add_library(luatestlib SHARED ${SRC_LIB_FILES} )

