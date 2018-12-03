#include <cstdint>

/*
 * Containers algorithms and iterators ->std::for_each(
 * c++11 -> lambda
 * Metaprogramming check of types in SetRequiredComponents
 */



#include "Components/NameComponent.h"
#include "Components/TestComponent2.h"
#include "Managers/World.h"
#include "Systems/Logger.h"
#include "Systems/Move.h"
#include "Components/Velocity.h"
#include <iostream>

int main() {

    World world;
    auto entity = world.CreateEntity();


    world.CreateEntity();
    world.CreateEntity();
    world.AddComponent(Velocity(1,1), entity);
    world.AddComponent(Position(0,0), entity);
    Logger logger(world);

    logger.Update();

    Move move(world);
    move.Update();

    logger.Update();
}


