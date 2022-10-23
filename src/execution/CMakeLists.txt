set (PROGRAM_SRC_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/src/include/execution/program_context.h
    ${PROJECT_SOURCE_DIR}/src/include/execution/state.h
)
add_library(
    program
    OBJECT
    program_context.cc
    # ${PROGRAM_SRC_INCLUDE_DIR}
)

target_include_directories(
    program PUBLIC ${PROJECT_SOURCE_DIR}/src/include/execution
)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:program>
        PARENT_SCOPE)
