add_subdirectory(algo)
add_subdirectory(execution)
add_subdirectory(main)
add_subdirectory(parser)
add_subdirectory(renderer)

# message("value of CMAKE_CURRENT_SOURCE_DIR" ${CMAKE_CURRENT_SOURCE_DIR})

# add_executable(coccoc ${ALL_OBJECT_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/core/test.cc)

set(COCCOC_LIBS
    algo
    parser
    renderer 
)

add_executable(coccoc ${ALL_OBJECT_FILES})

target_include_directories(
        coccoc PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
