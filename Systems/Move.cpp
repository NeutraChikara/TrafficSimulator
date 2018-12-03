//
// Created by Henrik Nielsen on 03/12/2018.
//

#include "Move.h"
#include "../Components/Position.h"
#include "../Components/Velocity.h"

Move::Move(World &world) : System(world) {
    SetRequiredComponents<Position, Velocity>();
}

void Move::OnUpdate(Entity e) {
    auto &pos = world.GetComponent<Position>(e.GetId());
    auto vel = world.GetComponent<Velocity>(e.GetId());

    pos.X += vel.Dx;
    pos.Y += vel.Dy;
}

