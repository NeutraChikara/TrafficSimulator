//
// Created by Henrik Nielsen on 19/11/2018.
//

#ifndef TRAFFICSIMULATOR_RENDER_H
#define TRAFFICSIMULATOR_RENDER_H

#include "System.h"

namespace Ecs::Systems {

class Render : public System {
public:
    Render(World &world, void(* loop)());
    void OnUpdate(Entity e) override;
    void Update() override;
    void Start();
};

}

#endif //TRAFFICSIMULATOR_RENDER_H
