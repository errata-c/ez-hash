
add_executable(hashing_test "main.cpp")
target_link_libraries(hashing_test PRIVATE fmt::fmt Catch2::Catch2WithMain ez::hash)