#pragma once
#include "../ecs/world.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{
    class MainMenuSystem
    {
        Application *app; // The application in which the state runs

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }
        // This should be called every frame to update all entities containing a GameOvertSystem.
        void update()
        {
            if (app->getKeyboard().isPressed(GLFW_KEY_SPACE))
            {
                //change state to play if we pressed space
                app->changeState("play");
            }
            else if (app->getKeyboard().isPressed(GLFW_KEY_ESCAPE))
            {
                //close app if we pressed escape
                app->close();
            }
        }
    };
}