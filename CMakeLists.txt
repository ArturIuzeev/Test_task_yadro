cmake_minimum_required(VERSION 3.27)
project(Test_task_yadro)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
add_executable(Test_task_yadro src/main.cpp
        src/application.cpp
        src/config.cpp
        src/tape.cpp)

enable_testing()

add_executable(
        my-test
        test/sort-test.cpp
        src/config.cpp
        src/tape.cpp
)
target_link_libraries(
        my-test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(my-test)