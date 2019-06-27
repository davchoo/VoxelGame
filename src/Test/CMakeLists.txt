find_package(Corrade REQUIRED TestSuite)

set(VoxelGameTests
        VoxelWorldTest.cpp)

# Copy Sources list and append ..
set(VoxelGameSourcesTest ${VoxelGameSources})
list(TRANSFORM VoxelGameSourcesTest PREPEND "../")

# Testing Executable
add_executable(VoxelGame_Test ${VoxelGameSourcesTest} ${VoxelGameTests})

# Testing Links
target_link_libraries(VoxelGame_Test Corrade::TestSuite)

# Tests
enable_testing()
corrade_add_test(VoxelWorldTest VoxelWorldTest.cpp)