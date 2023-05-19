#pragma once
#include "../ecs/world.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include "../../states/play-state.hpp"
#include "../../states/game-over-state.hpp"

namespace our
{

    class GameOverSystem {
        Application *app;         // The application in which the state runs
    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }
        // This should be called every frame to update all entities containing a GameOvertSystem.
        void update() {
            if(app->getKeyboard().isPressed(GLFW_KEY_ENTER)){
                // app->registerState<Playstate>("play");
                app->changeState("play");
                // app->registerState<GameOver>("game-over");
                // app->changeState("game-over");
            }
        }

    };

}
