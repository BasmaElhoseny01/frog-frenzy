#pragma once
#include "../ecs/world.hpp"
#include "../components/heart.hpp"
#include "../components/scope.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include "../../states/game-over-state.hpp"
#include "../../states/play-state.hpp"
#include "../ecs/entity.hpp"
#include <iostream>
using namespace std;
namespace our
{

    class CollisionSystem
    {
        Application *app;              // The application in which the state runs
        glm::vec3 positionFrog;        // position Frog
        int width = 20;                // width of ground
        int height = 40;               // height of ground
        Entity *heartEntity = nullptr; // Pointer to store heart entity
        Entity *frogEntity = nullptr;  // Pointer to store frog entity
        int counter = 0;

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
            counter = 0;
        }
        // This should be called every frame to update all entities containing a StreetComponent :D.
        void update(World *world, ForwardRenderer *forwardRenderer, bool &flagPostProcessing, ISoundEngine *engine, int &id)
        {

            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // Search for the frog entity
                if (entity->name == "frog")
                {
                    // get position of frog
                    positionFrog = entity->localTransform.position;
                    frogEntity = entity;
                    break;
                }
            }
            HeartComponent *heart = nullptr;
            ScopeComponent *scopeController = nullptr;
            for (auto entity : world->getEntities())
            {
                // Get name of entity
                std::string name = entity->name;
                // get the car's position
                glm::vec3 car_position = entity->localTransform.position;
                // If the bus or taxi component exists
                heart = entity->getComponent<HeartComponent>();
                if (heart && heart->id == id)
                {
                    // If heart with the specific id is found
                    heartEntity = entity;
                    continue;
                }

                // Get Scope Component to determines range of the taxi or car
                scopeController = entity->getComponent<ScopeComponent>();

                if ((name == "car" || name == "taxi") && scopeController)
                {
                    // get the car's max and min position
                    glm::vec3 car_size = scopeController->component_size;
                    glm::vec3 car_max = car_position + (car_size);
                    glm::vec3 car_min = car_position - (car_size);
                    if (positionFrog.x >= car_min.x && positionFrog.x <= car_max.x &&
                        positionFrog.z >= car_min.z && positionFrog.z <= car_max.z)
                    {
                        // check id to know which heart selected
                        if (id == 2)
                        {
                            flagPostProcessing = true;
                            forwardRenderer->setApplyPostProcessing(true); // Turn on Applying Post Processing
                            // frogEntity->localTransform.position[1] += height; // Make From Jump to the sky when last heart :(
                        }
                        else
                        {
                            id++;
                            // change position of heart selected Remove Heart from the lives menu
                            heartEntity->localTransform.position[1] = 100;
                            // change frog position after crash car Move Car to the front
                            frogEntity->localTransform.position[2] -= height;
                        }
                        // play sound
                        std::cout << "Basma: scream" << endl;
                        // engine->play2D("./media/scream.mp3", false);

                        // inc id after crash with the car
                    }
                }
            }
        }
        // Check if game is over
        void checkGameOver(bool flagPostProcessing)
        {
            // check if game is over or not
            if (flagPostProcessing)
            {
                counter++;
                // wait to apply post processing filter after 1.5 sec
                // _sleep(1500);
                if (counter >= 150)
                {
                    // cout << "ee";
                    // change to game over state
                    // app->registerState<GameOver>("game-over");
                    app->changeState("game-over");
                }
            }
        }
        void exit()
        {
            // Release Pointers
            app = nullptr;
            heartEntity = nullptr;
            frogEntity = nullptr;
        }
    };

}
