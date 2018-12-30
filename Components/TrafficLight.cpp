//
// Created by stud on 12/28/18.
//

#include "TrafficLight.h"

Ecs::Components::TrafficLight::TrafficLight() : IsDirectionAllowed{true, false, true, false}, CountsBeforeChange(300),
                                                LastChangedCounter(0) {

}
