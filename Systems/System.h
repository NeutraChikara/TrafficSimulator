//
// Created by Henrik Nielsen on 19/11/2018.
//

#ifndef TRAFFICSIMULATOR_SYSTEM_H
#define TRAFFICSIMULATOR_SYSTEM_H

#include "../Components/Component.h"
#include "../Components/ComponentUtility.h"
#include <tuple>
#include <vector>

class System {
public:
    template<typename Component, typename... Components>
    constexpr void SetRequiredComponents();
    void Update();

private:
    std::vector<unsigned int> IdsOfRequiredComponents;
};

template<typename ReqComponent, typename... ReqComponents>
constexpr void System::SetRequiredComponents() {
    static_assert( std::is_base_of<Component, ReqComponent>::value, "Passed type must be a subclass of Component");

    auto uniqueComponentTypeId = ComponentUtility<ReqComponent>::GetId();
    IdsOfRequiredComponents.push_back(uniqueComponentTypeId);

    if constexpr(sizeof...(ReqComponents) > 0)
        SetRequiredComponents<ReqComponents...>();
}

#endif //TRAFFICSIMULATOR_SYSTEM_H


