//
// Created by Henrik Nielsen on 03/12/2018.
//

#include "Move.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"

Move::Move(World &world) : System(world) {
    SetRequiredComponents<Transform, Velocity>();
}

void Move::OnUpdate(Entity e) {
    auto &pos = world.GetComponent<Transform>(e.GetId());
    auto vel = world.GetComponent<Velocity>(e.GetId());

    pos.X += vel.Dx;
    pos.Y += vel.Dy;
}

