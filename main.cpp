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
#include "Systems/Render.h"
#include <iostream>
static World world;
void Loop();
Logger logger(world);
Move move(world);
Render render(world,Loop);

int main() {
    auto entity = world.CreateEntity();

    world.CreateEntity();
    world.CreateEntity();
    world.AddComponent(Velocity(1,1), entity);
    world.AddComponent(Position(-1,-1), entity);

    render.Start();
}


void Loop(){
    logger.Update();
    move.Update();
    render.Update();
}