enable_testing()

add_executable(
        sentence_checker_tests
        sentence_checker_tests.cpp
)
target_link_libraries(
        sentence_checker_tests
        PRIVATE gmock_main
                gtest_main
                sentence_checker

)

target_include_directories(sentence_checker_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(sentence_checker_tests)