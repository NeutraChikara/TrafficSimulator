//
// Created by henrik on 27-11-2018.
//

#include "Entity.h"

namespace Ecs::Entities {
Entity::Id Entity::GetId() {
    return id;
}

Entity::Entity(Entity::Id id):id(id){

}
}