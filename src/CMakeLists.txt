include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(KILN_SRCS
    main.cpp
    kiln.cpp
)

add_executable(kiln ${KILN_SRCS})

target_link_libraries(kiln KF5::AtCore KF5::Solid)
