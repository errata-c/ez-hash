
add_executable(utility_test "main.cpp")
target_link_libraries(utility_test PRIVATE ez::hash Catch2::Catch2WithMain fmt::fmt)