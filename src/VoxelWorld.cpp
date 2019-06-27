//
// Created by davchoo on 6/23/2019.
//

#include "VoxelWorld.h"

#include <utility>

#include <glm/gtc/integer.hpp>
#include <glm/common.hpp>


Voxel& VoxelChunk::getVoxel(glm::ivec3 voxelPos) {
    return voxels[VoxelChunk::Size * VoxelChunk::Size * voxelPos.y + VoxelChunk::Size * voxelPos.z + voxelPos.x];
}

VoxelChunk::VoxelChunk(glm::ivec3 chunkLocation) : chunkLocation(chunkLocation) {}

VoxelChunk VoxelWorldGenerator::genChunk(glm::ivec3 chunkPos) {
    VoxelChunk chunk{chunkPos};
    return chunk;
}

VoxelWorld::VoxelWorld(Containers::Pointer<VoxelWorldGenerator> worldGenerator) {
    this->worldGenerator = std::move(worldGenerator);
}

VoxelChunk& VoxelWorld::getChunk(glm::ivec3 chunkPos) {
    auto chunkPair = chunks.find(chunkPos);
    if (chunkPair == chunks.end()) {
        VoxelChunk chunk = worldGenerator->genChunk(chunkPos);
        chunkPair = chunks.insert({chunkPos, std::move(chunk)}).first;
    }
    return chunkPair->second;
}

Voxel& VoxelWorld::getVoxel(glm::ivec3 voxelPos) {
    glm::ivec3 chunkPos = voxelPos / VoxelChunk::Size;
    glm::ivec3 relVoxelPos{voxelPos.x % VoxelChunk::Size, voxelPos.y % VoxelChunk::Size, voxelPos.z % VoxelChunk::Size};
    VoxelChunk& chunk = getChunk(chunkPos);
    return chunk.getVoxel(relVoxelPos);
}