//
// Created by henrik on 27-11-2018.
//

#ifndef TRAFFICSIMULATOR_ENTITY_H
#define TRAFFICSIMULATOR_ENTITY_H

namespace Ecs::Entities {

class Entity {
public:
    // TODO: Genovervej brugen af using Id
    using Id = int;

    Entity(Id id);

    Id GetId();

private:
    Id id;
};
}

#endif //TRAFFICSIMULATOR_ENTITY_H
