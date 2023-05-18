#pragma once
#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include "../../states/game-over-state.hpp"

namespace our
{

    class CollisionSystem {
        Application *app;         // The application in which the state runs
        glm::vec3 positionFrog;
        glm::vec3 positionScale;
        int width = 20;
        int height = 40;
        vector<Entity> cars;
    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }
        // This should be called every frame to update all entities containing a StreetComponent.
        void update(World* world) {
            // For each entity in the world
            for(auto entity : world->getEntities()){
                if (entity->name=="frog")
                {
                    // get position of frog
                    positionFrog = entity->localTransform.position;
                    break;
                }
            }
           
            for(auto entity : world->getEntities()){
                // Get name of entity
                std::string name = entity->name;
                // get the car's position
                glm::vec3 car_position = entity->localTransform.position;
                // If the bus or taxi component exists
                if((name=="bus")){
                    // get the car's max and min position
                    glm::vec3 bus_size =  glm::vec3(13, 0, 3);
                    glm::vec3 car_max = car_position + (bus_size  );
                    glm::vec3 car_min = car_position - (bus_size );
                    if (positionFrog.x >= car_min.x && positionFrog.x <= car_max.x &&
                            positionFrog.y >= car_min.y && positionFrog.y <= car_max.y &&
                            positionFrog.z >= car_min.z && positionFrog.z <= car_max.z)
                        {
                            app->registerState<GameOver>("game-over");
                            app->changeState("game-over");
                        }
                }
                if((name=="taxi")){
                 

                    // get the car's max and min position
                    glm::vec3 taxi_size =  glm::vec3(6, 0, 3);
                    glm::vec3 car_max = car_position + (taxi_size  );
                    glm::vec3 car_min = car_position - (taxi_size );
                    if (positionFrog.x >= car_min.x && positionFrog.x <= car_max.x &&
                            positionFrog.y >= car_min.y && positionFrog.y <= car_max.y &&
                            positionFrog.z >= car_min.z && positionFrog.z <= car_max.z)
                        {
                            app->registerState<GameOver>("game-over");
                            app->changeState("game-over");
                        }
                }
            }
        }

    };

}
