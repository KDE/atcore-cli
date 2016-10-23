include_directories(../atcore)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(KILN_SRCS
    main.cpp
)

add_executable(Kiln ${KILN_SRCS})
add_dependencies(Kiln AtCoreLib)

target_link_libraries(Kiln AtCoreLib KF5::Solid)
