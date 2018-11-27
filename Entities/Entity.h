//
// Created by henrik on 27-11-2018.
//

#ifndef TRAFFICSIMULATOR_ENTITY_H
#define TRAFFICSIMULATOR_ENTITY_H


#include <cstdint>

class Entity {
public:
    using Id = uint8_t;
    Entity(Id id);
private:
    Id id;
};


#endif //TRAFFICSIMULATOR_ENTITY_H
