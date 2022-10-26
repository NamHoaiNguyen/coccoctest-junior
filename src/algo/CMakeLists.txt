set (ALGO_SRC_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/src/include/algo
)

set (ALGO_INCLUDE_FILES
    ${PROJECT_SOURCE_DIR}/src/include/algo/algo.h
    ${PROJECT_SOURCE_DIR}/src/include/common/command_data.h
)

message(${ALGO_SRC_INCLUDE_DIR})


add_library(
    algo
    OBJECT
    algo.cc
    dimension_command.cc
    line_command.cc
    move_command.cc
    ${ALGO_INCLUDE_FILES}
)

target_include_directories(
    algo PUBLIC ${PROJECT_SOURCE_DIR}/src/include/algo
    algo PUBLIC ${PROJECT_SOURCE_DIR}/src/include/common
    algo PUBLIC ${PROJECT_SOURCE_DIR}/src/include/parser
)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:algo>
        PARENT_SCOPE)