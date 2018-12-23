//
// Created by stud on 12/23/18.
//

#include "Render.h"

Ecs::Components::Render::Render(std::string type, struct Color color) : Type(std::move(type)),
Color(color) {}