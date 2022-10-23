add_library(
    renderer
    OBJECT
    test.cc
)

set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:renderer>
        PARENT_SCOPE)