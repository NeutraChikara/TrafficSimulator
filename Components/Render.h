//
// Created by Henrik Nielsen on 19/12/2018.
//

#ifndef TRAFFICSIMULATOR_COMPONENTS_RENDER_H
#define TRAFFICSIMULATOR_COMPONENTS_RENDER_H


#include "Component.h"
#include "../Helpers/Color.h"
#include <string>

using namespace Ecs::Helpers;

namespace Ecs::Components {
    struct Render : Component {
        Render(std::string type = "unknown", Color color = {0.5, 0.5, 0.5});

        std::string Type;
        struct Color Color;
    };
}

#endif //TRAFFICSIMULATOR_RENDER_H
