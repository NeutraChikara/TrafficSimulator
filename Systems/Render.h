//
// Created by Henrik Nielsen on 19/11/2018.
//

#ifndef TRAFFICSIMULATOR_RENDER_H
#define TRAFFICSIMULATOR_RENDER_H

#include "System.h"



class Render : public System {
public:
    Render(World &world, void(* loop)(void));
    void OnUpdate(Entity e);
    void Update();
    void Start();
};


#endif //TRAFFICSIMULATOR_RENDER_H
