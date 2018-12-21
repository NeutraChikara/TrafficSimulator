//
// Created by Henrik Nielsen on 19/12/2018.
//

#include "Velocity.h"

Ecs::Components::Velocity::Velocity(unsigned int maxSpeed, unsigned int speed, unsigned int acceleration,
                                    unsigned int deceleration) : MaxSpeed(maxSpeed), Speed(speed),
                                                                 Acceleration(acceleration),
                                                                 Deceleration(deceleration) {

}
