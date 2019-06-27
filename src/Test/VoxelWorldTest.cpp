//
// Created by davchoo on 6/25/2019.
//

#include <Corrade/TestSuite/Tester.h>

#include "../VoxelWorld.h"

#include <glm/common.hpp>

namespace {
    using namespace Corrade;

    class VoxelWorldTest : public TestSuite::Tester {
    public:
        explicit VoxelWorldTest();
        void constructVoxelChunk();
        void constructVoxelWorld();

        void generateVoxelChunk();

        void accessVoxelInVoxelChunk();

        void accessChunkInVoxelWorld();
        void accessVoxelInVoxelWorld();
    };

    VoxelWorldTest::VoxelWorldTest() {
        addTests({
            &VoxelWorldTest::constructVoxelChunk,
            &VoxelWorldTest::constructVoxelWorld,

            &VoxelWorldTest::generateVoxelChunk,

            &VoxelWorldTest::accessVoxelInVoxelChunk,

            &VoxelWorldTest::accessChunkInVoxelWorld,
            &VoxelWorldTest::accessVoxelInVoxelWorld,
        });
    }

    void VoxelWorldTest::constructVoxelChunk() {
        glm::ivec3 chunkPos{1, 2, 3};
        VoxelChunk chunk{chunkPos};

        CORRADE_VERIFY(glm::all(glm::equal(chunkPos, chunk.chunkLocation)));
    }

    void VoxelWorldTest::constructVoxelWorld() {
        Containers::Pointer<VoxelWorldGenerator> worldGenerator{new VoxelWorldGenerator};
        VoxelWorld voxelWorld{std::move(worldGenerator)};

        CORRADE_VERIFY(voxelWorld.worldGenerator != nullptr);
    }

    void VoxelWorldTest::generateVoxelChunk() {
        Containers::Pointer<VoxelWorldGenerator> worldGenerator{new VoxelWorldGenerator};
        glm::ivec3 chunkPos = {1, 2, 3};
        VoxelChunk chunk = worldGenerator->genChunk(chunkPos);

        CORRADE_VERIFY(glm::all(glm::equal(chunk.chunkLocation, chunkPos)));
    }

    void VoxelWorldTest::accessVoxelInVoxelChunk() {
        VoxelChunk chunk{{1, 2, 3}};
        // Checking every voxel is slow
        int stepSize = 128;
        for (int y = 0; y < VoxelChunk::Size; y+=stepSize) {
            for (int z = 0; z < VoxelChunk::Size; z+=stepSize) {
                for (int x = 0; x < VoxelChunk::Size; x+=stepSize) {
                    int pos = y * VoxelChunk::Size * VoxelChunk::Size + z * VoxelChunk::Size + x;
                    Voxel& voxel = chunk.getVoxel({x, y, z});
                    // Check that the voxel hasn't been modified before
                    CORRADE_COMPARE(voxel.type, -1);

                    // Check that modifying the reference modifies the voxel in the array
                    voxel.type = pos;
                    CORRADE_COMPARE(chunk.getVoxel({x, y, z}).type, pos);

                    // Check that the voxel modified is at the right position in the array
                    CORRADE_COMPARE(chunk.voxels[pos].type, pos);
                }
            }
        }
    }

    void VoxelWorldTest::accessChunkInVoxelWorld() {
        Containers::Pointer<VoxelWorldGenerator> worldGenerator{new VoxelWorldGenerator};
        VoxelWorld voxelWorld{std::move(worldGenerator)};
        glm::ivec3 chunkPos{1, 2, 3};
        VoxelChunk& chunk = voxelWorld.getChunk(chunkPos);
        // Verify chunk location is set
        CORRADE_VERIFY(glm::all(glm::equal(chunk.chunkLocation, chunkPos)));
    }

    void VoxelWorldTest::accessVoxelInVoxelWorld() {
        Containers::Pointer<VoxelWorldGenerator> worldGenerator{new VoxelWorldGenerator};
        VoxelWorld voxelWorld{std::move(worldGenerator)};

        // Hard coded test pos
        glm::ivec3 voxelPos{VoxelChunk::Size, 0, 0};
        glm::ivec3 expectedChunkPos{1, 0, 0};
        glm::ivec3 expectedRelPos{0, 0, 0};
        int testVoxelType = 100;

        Voxel& testVoxel = voxelWorld.getVoxel(voxelPos);
        testVoxel.type = testVoxelType;
        VoxelChunk& chunk = voxelWorld.getChunk(expectedChunkPos);
        Voxel& expectedVoxel = chunk.getVoxel(expectedRelPos);

        CORRADE_COMPARE(&testVoxel, &expectedVoxel);
        CORRADE_COMPARE(expectedVoxel.type, testVoxelType);
    }

}

CORRADE_TEST_MAIN(VoxelWorldTest)