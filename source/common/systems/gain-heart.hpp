#pragma once
#include "../ecs/world.hpp"
#include "../components/scope.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include "../../states/game-over-state.hpp"
#include "../../states/play-state.hpp"
#include "../ecs/entity.hpp"
#include "../components/heart.hpp"
#include <iostream>
using namespace std;
#include "glm/gtx/string_cast.hpp"

namespace our
{

    class GainHeartSystem
    {
        glm::vec3 positionFrog;

    public:
        // This should be called every frame to update all entities containing a StreetComponent.
        void update(World *world, int &id)
        {
            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                if (entity->name == "frog")
                {
                    // get position of frog
                    positionFrog = entity->localTransform.position;
                    break;
                }
            }

            // Check on postion of frog relative to the Hearts in the system
            for (auto entity : world->getEntities())
            {
                // Get name of entity
                std::string name = entity->name;
                if (name == "heart gain")
                {
                    // If Already there is
                    //  get the heart's position
                    glm::vec3 heart_position = entity->localTransform.position;

                    // Get Scope Component for this entity
                    ScopeComponent *scope = entity->getComponent<ScopeComponent>();
                    if (scope)
                    {
                        // Scope Component Exists
                        glm::vec3 heart_size = scope->component_size;
                        glm::vec3 heart_max = heart_position + (heart_size);
                        glm::vec3 heart_min = heart_position - (heart_size);
                        // If Frog Passed the Heart :( Move it
                        // if (positionFrog.z <= heart_max.z)
                        // {
                        //     int x_old = entity->localTransform.position[0];
                        //     int x_rand = 0 + (std::rand() % (35 + 1)); // random number from 0-35
                        //     if (x_old > 0)
                        //     {
                        //         x_rand *= -1;
                        //     }
                        //     entity->localTransform.position[0] += x_rand;
                        //     cout << "x_rand" << x_rand << endl;
                        //     // change z [70-100]
                        //     int z_rand = 60 + (std::rand() % (100 + 1 - 60));
                        //     entity->localTransform.position[2] -= z_rand;
                        //     cout << "z_rand" << z_rand << endl;
                        //     cout << "Frog Postion:" << glm::to_string(positionFrog) << endl;
                        // }
                        if (positionFrog.x >= heart_min.x && positionFrog.x <= heart_max.x && positionFrog.z >= heart_min.z && positionFrog.z <= heart_max.z)
                        {
                            if (id <= 0)
                            {
                                // Full Heart Level
                                break;
                            }
                            // Increase Heart Count
                            cout << "Increase Heart Counts :D" << endl;
                            id -= 1;

                            // min + rand() % (( max + 1 ) - min);
                            // Move the heart Forward !!!!!
                            // Change x [0-35 or -35-0]
                            int x_old = entity->localTransform.position[0];
                            int x_rand = 0 + (std::rand() % (35 + 1)); // random number from 0-35
                            if (x_old > 0)
                            {
                                x_rand *= -1;
                            }
                            entity->localTransform.position[0] += x_rand;
                            cout << "x_rand" << x_rand << endl;
                            // change z [60-100]
                            int z_rand = 60 + (std::rand() % (100 + 1 - 60));
                            entity->localTransform.position[2] -= z_rand;
                            cout << "z_rand" << z_rand << endl;
                            cout << "Frog Postion:" << glm::to_string(positionFrog) << endl;
                        }
                    }
                }
            }
            HeartComponent *heart = nullptr;
            for (auto entity : world->getEntities()){
                heart = entity->getComponent<HeartComponent>();
                if(heart && heart->id==id){
                    entity->localTransform.position.y = 20;
                    break;
                }
            }
        }
        void exit()
        {
        }
    };
}