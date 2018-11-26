//
// Created by henrik on 26-11-2018.
//

#ifndef TRAFFICSIMULATOR_COMPONENTUTILITY_H
#define TRAFFICSIMULATOR_COMPONENTUTILITY_H


struct ComponentUtilityHelper
{
    ComponentUtilityHelper() = delete;
    using Id = unsigned int;
protected:
    static Id id_counter;
};

// Used to assign a unique id to a component type, we don't really have to make our components derive from this though.
template <typename T>
struct ComponentUtility : ComponentUtilityHelper
{
    ComponentUtility() = delete;
    // Returns the unique id of Component<T>
    static Id GetId() {
        static auto id = id_counter++;
        return id;
    }

};


#endif //TRAFFICSIMULATOR_COMPONENTUTILITY_H
