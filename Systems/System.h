//
// Created by Henrik Nielsen on 19/11/2018.
//

#ifndef TRAFFICSIMULATOR_SYSTEM_H
#define TRAFFICSIMULATOR_SYSTEM_H

#include <tuple>

class System {
public:
    template<typename... Components>
    void SetRequiredComponents(Components... components);
};

template<typename... Components>
void System::SetRequiredComponents(Components... componentsArg) {
    std::tuple<Components...> components{componentsArg...};

}


#endif //TRAFFICSIMULATOR_SYSTEM_H