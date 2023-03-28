file(GLOB_RECURSE PROTOFILE "cpp_proto/*.pb.*")
file(GLOB_RECURSE SRC_FILES "*.cpp") # "src/pattern/*.cpp" "src/pattern/*.h" "src/net/*.cpp" "src/restudy/*.cpp" "src/cpu/*.cpp" "src/zookeeper/*.cpp" "src/rapidjson/*.cpp" "src/uv_test/*.cpp" )

# aux_source_directory("src" SRC_FILES)
list(APPEND SRC_FILES ${PROTOFILE})
list(APPEND SRC_FILES ${UTILFILE})
file(GLOB_RECURSE SRC_HEADS "*.h")

find_file(exe_build NAMES AllCppTest PATHS .)

# add_custom_command(OUTPUT ${exe_log} COMMAND echo "nice")
# 绝对路径

# macro(use_precompiled_header TARGET HEADER_FILE SRC_FILE)
# get_filename_component(HEADER ${HEADER_FILE} NAME)
# # Use MSVC_IDE to exclude NMake from using PCHs
# if (MSVC AND NOT NMAKE AND NOT OGRE_UNITY_BUILD)
# set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS /Yu"${HEADER}")
# set_source_files_properties(${SRC_FILE}
# PPROPERTIES COMPILE_FLAGS /Yc"${HEADER}"
# )
# elseif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
# endif ()
# endmacro(use_precompiled_header)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${WORKING_DIRECTORY}/bin)
add_executable(AllCppTest ${SRC_FILES} ${SRC_HEADS})
target_link_libraries(AllCppTest ${ALL_LIBS})

# add_dependencies(AllCppTest protobuild)