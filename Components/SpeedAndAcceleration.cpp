//
// Created by Henrik Nielsen on 19/12/2018.
//

#include "SpeedAndAcceleration.h"

Ecs::Components::SpeedAndAcceleration::SpeedAndAcceleration(unsigned int maxSpeed, unsigned int speed, unsigned int acceleration,
                                    unsigned int deceleration) : MaxSpeed(maxSpeed), Speed(speed),
                                                                 Acceleration(acceleration),
                                                                 Deceleration(deceleration) {

}
