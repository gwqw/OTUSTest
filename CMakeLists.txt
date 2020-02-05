cmake_minimum_required(VERSION 3.2)

# build number for travis
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(range VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(range VERSION 0.0.1)
endif()

# boost dependensies
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Threads REQUIRED)

# executable target
set(EXE_NAME hello)
add_executable(${EXE_NAME} main.cpp hello.h)
add_executable(test_hello test_hello.cpp hello.h)

# compiler options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(CMP_OPTIONS "-Wpedantic;-Wall;-Wextra")#;-fsanitize=thread")
else()
  set(CMP_OPTIONS "/W4")
endif()

# target properties
set_target_properties(${EXE_NAME} test_hello
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS ${CMP_OPTIONS}
    #LINK_OPTIONS "-fsanitize=thread"
)

if(UNIX)
    set_target_properties(test_hello PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    )
endif()

set_target_properties(test_hello PROPERTIES
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

# target linking
target_link_libraries(${EXE_NAME} Threads::Threads)
target_link_libraries(test_hello
    ${Boost_LIBRARIES}
)

# installation
install(TARGETS ${EXE_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT gwrass@mail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

# tests
enable_testing()

add_test(ip_tests bin/test_hello)

