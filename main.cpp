#include <utility>

#include <cstdint>

/*
 * Containers algorithms and iterators ->std::for_each( use functor TODO
 * c++11 -> lambda
 * Metaprogramming check of types in SetRequiredComponents
 * Throw Render exception hvis component mangler TODO
 * Namespaces
 */

#include "Components/Render.h"
#include "Managers/World.h"
#include "Systems/Logger.h"
#include "Systems/Move.h"
#include "Components/Velocity.h"
#include "Systems/Render.h"
#include "Components/Path.h"
#include "Components/Node.h"
#include "Systems/TrafficLightControl.h"
#include "Components/TrafficLight.h"
#include <iostream>

using namespace Ecs::Components;
using namespace Ecs::Systems;

void Loop();

static World world;
Logger logger(world);
Move move(world);
Ecs::Systems::Render render(world, Loop);
TrafficLightControl trafficLight(world);

void CreateCarEntity(int x, int y, int velX, int velY, Path path) {
    auto entity = world.CreateEntity();
    world.AddComponent(Velocity(velX, velY), entity);
    world.AddComponent(Transform(x, y, 0), entity);
    world.AddComponent(std::move(path), entity);
    world.AddComponent(Ecs::Components::Render("car"), entity);
}

int CreateTrafficLightEntity() {
    auto entity = world.CreateEntity();
    world.AddComponent(TrafficLight(), entity);
    return entity.GetId();
}

int main() {
    auto lightId = CreateTrafficLightEntity();
    Path path;
    path.Path.emplace_back(500,500, lightId);
    path.Path.emplace_back(1000,0, lightId);
    CreateCarEntity(0, 0, 10, 0, path);
    render.Start();
}

void Loop() {
    logger.Update();
    trafficLight.Update();
    move.Update();
    render.Update();
}