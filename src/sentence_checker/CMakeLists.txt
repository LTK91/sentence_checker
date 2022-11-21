add_library(sentence_checker sentence_checker.cpp)

target_link_libraries(sentence_checker
                      PUBLIC logger)