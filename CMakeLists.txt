cmake_minimum_required(VERSION 3.5)
project(pattern)

add_executable(async_client chat_client.cpp chat_message.hpp)
add_executable(async_server chat_server.cpp chat_message.hpp)

set_target_properties(async_client PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED OFF
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
set_target_properties(async_server PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED OFF
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

find_package(Boost COMPONENTS system unit_test_framework)
find_package(Threads REQUIRED)

include_directories(async_client ${Boost_INCLUDE_DIR})
target_link_libraries(async_client ${Boost_LIBRARIES})
include_directories(async_server ${Boost_INCLUDE_DIR})
target_link_libraries(async_server ${Boost_LIBRARIES})

target_link_libraries(async_client Threads::Threads)
target_link_libraries(async_server Threads::Threads)

#set_target_properties(test PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK)