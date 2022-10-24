add_library(
    renderer
    OBJECT
    bitmap.cc
    console.cc
)

target_include_directories(
    renderer PUBLIC ${PROJECT_SOURCE_DIR}/src/include/renderer
    # renderer PUBLIC ${PROJECT_SOURCE_DIR}/src/include/algo
    # renderer PUBLIC ${PROJECT_SOURCE_DIR}/src/include/execution
)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:renderer>
        PARENT_SCOPE)