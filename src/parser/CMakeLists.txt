# set(COCCOC_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

set (PARSER_SRC_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/src/include/parser/parser.h
    # ${PROJECT_SOURCE_DIR}/src/include/parser/command.h
    # ${PROJECT_SOURCE_DIR}/src/include/parser/move_command.h
    # ${PROJECT_SOURCE_DIR}/src/include/parser/dimension_command.h
    # ${PROJECT_SOURCE_DIR}/src/include/parser/line_command.h

    ${PROJECT_SOURCE_DIR}/src/include/execution/state.h
    ${PROJECT_SOURCE_DIR}/src/include/common/command_data.h
)

message(${PROJECT_SOURCE_DIR}/src/include/common/command_data.h)

add_library(
    parser
    OBJECT
    parser.cc
    ${PARSER_SRC_INCLUDE_DIR}
)

target_include_directories(
    parser PUBLIC ${PROJECT_SOURCE_DIR}/src/include/common
    parser PUBLIC ${PROJECT_SOURCE_DIR}/src/include/parser
    parser PUBLIC ${PROJECT_SOURCE_DIR}/src/include/execution
)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:parser>
        PARENT_SCOPE)
