//
// Created by davchoo on 6/23/2019.
//

#ifndef VOXELGAME_VOXELWORLD_H
#define VOXELGAME_VOXELWORLD_H

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Pointer.h>
#include <Corrade/Containers/StridedArrayView.h>

#include <glm/common.hpp>
#include <glm/vec3.hpp>

#include <map>

using namespace Corrade;


struct Voxel {
    float value = 0;
    int type = -1;
};

class VoxelChunk {
public:
    static constexpr int Size = 512;
    Containers::Array<Voxel> voxels{Size * Size * Size};
    glm::ivec3 chunkLocation;

    explicit VoxelChunk(glm::ivec3 chunkLocation);
    Voxel& getVoxel(glm::ivec3 voxelPos);
};

class VoxelWorldGenerator {
public:
    virtual VoxelChunk genChunk(glm::ivec3 chunkPos);
};

class VoxelWorld {
public:
    class ChunkPosComparator {
    public:
        bool operator()(const glm::ivec3& rhs, const glm::ivec3& lhs){
            return glm::all(glm::lessThan(rhs, lhs));
        }
    };

    Containers::Pointer<VoxelWorldGenerator> worldGenerator;
    std::map<glm::ivec3, VoxelChunk, VoxelWorld::ChunkPosComparator> chunks;

    explicit VoxelWorld(Containers::Pointer<VoxelWorldGenerator> worldGenerator);
    VoxelChunk& getChunk(glm::ivec3 chunkPos);
    Voxel& getVoxel(glm::ivec3 voxelPos);
};


#endif //VOXELGAME_VOXELWORLD_H
