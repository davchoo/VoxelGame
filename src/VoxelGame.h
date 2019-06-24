#ifndef PLATFORMING_VOXELGAME_H
#define PLATFORMING_VOXELGAME_H

#include <Magnum/Platform/Sdl2Application.h>

using namespace Magnum;

class VoxelGame : public Platform::Application {
public:
    explicit VoxelGame(const Arguments &arguments);

private:
    void drawEvent() override;
};


#endif //PLATFORMING_VOXELGAME_H
