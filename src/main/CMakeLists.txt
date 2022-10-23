set (MAIN_SRC_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/src/include/algo
    ${PROJECT_SOURCE_DIR}/src/include/parser
    ${PROJECT_SOURCE_DIR}/src/include/execution
    ${PROJECT_SOURCE_DIR}/src/include/renderer
)

# set (MAIN_INCLUDE_FILES
#     ${PROJECT_SOURCE_DIR}/src/include/algo/algo.h
# )


message(${PROJECT_SOURCE_DIR}/src/include)


add_library(
    main
    OBJECT
    main.cc
    # ${MAIN_INCLUDE_FILES}
)

target_include_directories(
    main PUBLIC ${MAIN_SRC_INCLUDE_DIR}
)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:main>
        PARENT_SCOPE)