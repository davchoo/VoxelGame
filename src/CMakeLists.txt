find_package(Magnum REQUIRED Audio GL Sdl2Application MeshTools Primitives Shaders Text)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

corrade_add_resource(VoxelGameResources ../res/resources.conf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(VoxelGame
        ${VoxelGameResources} VoxelGame.cpp VoxelGame.h)

target_link_libraries(VoxelGame PRIVATE
    Magnum::Application
    Magnum::Audio
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::Shaders
    Magnum::Text)
