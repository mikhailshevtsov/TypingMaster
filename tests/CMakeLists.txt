include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_EXECUTABLE_NAME TypingMasterTests)

add_executable(${TEST_EXECUTABLE_NAME}
    Test_main.cpp
    TypingSourceTest.cpp)

target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE GTest::gtest_main TypingMasterLibrary)

#enable_testing()
#include(GoogleTest)
#gtest_discover_tests(${TEST_EXECUTABLE_NAME})
#add_test(NAME ${TEST_EXECUTABLE_NAME} COMMAND ${TEST_EXECUTABLE_NAME})
