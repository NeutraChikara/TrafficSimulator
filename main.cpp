#include <cstdint>
#include <malloc.h>

/*
 * Containers algorithms and iterators ->std::for_each(
 * c++11 -> lambda
 */



#include "Components/NameComponent.h"
#include "Components/TestComponent2.h"
#include "Managers/World.h"
#include "Systems/Logger.h"
#include <iostream>

int main() {

    World world;
    auto entity = world.CreateEntity();


    world.CreateEntity();
    world.CreateEntity();
    world.AddComponent(NameComponent() ,entity);
    Logger logger(world);



    logger.Update();
}


