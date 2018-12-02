#include <cstdint>
#include <malloc.h>

/*
 * GL06TimerFunc.cpp: Translation and Rotation
 * Transform primitives from their model spaces to world space (Model Transform).
 */



#include "Systems/System.h"
#include "Systems/Render.h"
#include "Components/TestComponent1.h"
#include "Components/TestComponent2.h"
#include "Components/ComponentUtility.h"
#include "Managers/World.h"
#include "Systems/Logger.h"
#include <iostream>

int main() {
//    System system;
//    system.SetRequiredComponents<TestComponent1, TestComponent2>();
    World world;
    auto entity = world.CreateEntity();
    world.CreateEntity();
    world.CreateEntity();
    Logger logger(world);
   // entity.AddComponent<TestComponent1>();
    //entity.AddComponent<TestComponent2>(10);

    //std::cout << ComponentUtility<TestComponent1>::GetId() << std::endl;
    //std::cout << ComponentUtility<TestComponent2>::GetId() << std::endl;
    //std::cout << ComponentUtility<TestComponent1>::GetId() << std::endl;
    //std::cout << ComponentUtility<TestComponent2>::GetId() << std::endl;

    logger.Update();
}


