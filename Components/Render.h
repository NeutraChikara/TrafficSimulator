//
// Created by Henrik Nielsen on 19/12/2018.
//

#ifndef TRAFFICSIMULATOR_COMPONENTS_RENDER_H
#define TRAFFICSIMULATOR_COMPONENTS_RENDER_H


#include "Component.h"
#include <string>

namespace Ecs::Components {
    struct Render : Component {
        Render(std::string type = "unknown", std::string color = "grey") : Type(std::move(type)), Color(std::move(color)) {}
        std::string Type;
        std::string Color;
    };
}

#endif //TRAFFICSIMULATOR_RENDER_H
