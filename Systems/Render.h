//
// Created by Henrik Nielsen on 19/11/2018.
//

#ifndef TRAFFICSIMULATOR_RENDER_H
#define TRAFFICSIMULATOR_RENDER_H

#include "System.h"

namespace Ecs::Systems {

    class Render : public System {
    public:
        Render(World &world, void(*loop)());

        void OnUpdate(Entity e) override;

        void Update() override;

        virtual ~Render();

        void Start();

        void Setup(int argc, char **argv, void (*loop)());
    private:
        class InputHandler : private System {
        public:
            InputHandler(World &world);
            static void KeyPressedWrapper(unsigned char key, int x, int y);
            void KeyPressed(unsigned char key, int x, int y);

        private:
            void OnUpdate(Entity e) override;

            bool Increase;

        };

        static InputHandler *Instance;
    };

}

#endif //TRAFFICSIMULATOR_RENDER_H
