//
// Created by Henrik Nielsen on 19/11/2018.
//

#ifndef TRAFFICSIMULATOR_SYSTEM_H
#define TRAFFICSIMULATOR_SYSTEM_H

#include "../Components/Component.h"
#include "../Components/ComponentUtility.h"
#include "../Managers/World.h"
#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>

namespace {
class System {
public:
    template<typename Component, typename... Components>
    constexpr void SetRequiredComponents();
    World & world;
    System(World & world);

    void Update();

    virtual void OnUpdate(Entity e) = 0;

private:
    std::vector<unsigned int> IdsOfRequiredComponents;

    bool HasRequiredComponents(Entity entity);
};

template<typename ReqComponent, typename... ReqComponents>
constexpr void System::SetRequiredComponents() {
    static_assert(std::is_base_of<Component, ReqComponent>::value, "Passed type must be a subclass of Component");

    auto uniqueComponentTypeId = ComponentUtility<ReqComponent>::GetId();
    IdsOfRequiredComponents.push_back(uniqueComponentTypeId);

    if constexpr(sizeof...(ReqComponents) > 0)
        SetRequiredComponents<ReqComponents...>();
}

void System::Update() {
    std::cout << "System::Update()" << std::endl;
    std::for_each(world.createdEntities.begin(), world.createdEntities.end(),[this](Entity e){
        if(HasRequiredComponents(e))
            OnUpdate(e);});
}

System::System(World & world):world(world) {

}

bool System::HasRequiredComponents(Entity entity) {
    return true;
}
}


#endif //TRAFFICSIMULATOR_SYSTEM_H


