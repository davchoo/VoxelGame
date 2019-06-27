find_package(Magnum REQUIRED Audio GL Sdl2Application MeshTools Primitives Shaders Text)

# Config
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

# Resources
corrade_add_resource(VoxelGameResources ../res/resources.conf)

# Sources
set(VoxelGameSources
        VoxelWorld.cpp)

# Executable
add_executable(VoxelGame
        ${VoxelGameResources} VoxelGame.cpp ${VoxelGameSources})

# Links
target_link_libraries(VoxelGame PRIVATE
        Magnum::Application
        Magnum::Audio
        Magnum::GL
        Magnum::Magnum
        Magnum::MeshTools
        Magnum::Primitives
        Magnum::Shaders
        Magnum::Text)

# Testing
add_subdirectory(Test)