//
// Created by Henrik Nielsen on 19/11/2018.
//

#ifndef TRAFFICSIMULATOR_SYSTEM_H
#define TRAFFICSIMULATOR_SYSTEM_H

#include "../Components/ComponentUtility.h"
#include "../Managers/World.h"
#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>

class System {
public:
    template<typename Component, typename... Components>
    constexpr void SetRequiredComponents();
    World & world;
    System(World & world);

    void Update();

protected:
    virtual void OnUpdate(Entity e) = 0;

private:
    unsigned int RequiredComponentsMask =0;

    bool HasRequiredComponents(Entity entity);
};

template<typename ReqComponent, typename... ReqComponents>
constexpr void System::SetRequiredComponents() {
    static_assert(std::is_base_of<Component, ReqComponent>::value, "Passed type must be a subclass of Component");

    RequiredComponentsMask |= 1 <<ComponentUtility<ReqComponent>::GetId();

    if constexpr(sizeof...(ReqComponents) > 0)
        SetRequiredComponents<ReqComponents...>();

}


#endif //TRAFFICSIMULATOR_SYSTEM_H


