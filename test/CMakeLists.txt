# Test CMake configuration

# Build the tests
add_executable(DumbTests test.cpp)

# Link the test executable against the main library
target_link_libraries(DumbTests DumbDB)
