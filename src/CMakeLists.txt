include_directories(../atcore)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(KILN_SRCS
    main.cpp
    kiln.cpp
)

add_executable(kiln ${KILN_SRCS})
add_dependencies(kiln AtCoreLib)

target_link_libraries(kiln AtCoreLib KF5::Solid)
