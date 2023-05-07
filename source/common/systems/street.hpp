#pragma once

#include "../ecs/world.hpp"
#include "../components/street.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    class StreetSystem {
        glm::vec4 positionCamera;
        int width = 20;
        int height = 40;

    public:

        // This should be called every frame to update all entities containing a StreetComponent. 
        void update(World* world) {
            // For each entity in the world
            for(auto entity : world->getEntities()){
                // Get the camera component if it exists
                CameraComponent* camera = entity->getComponent<CameraComponent>();
                // If the street component exists
                if (camera)
                {
                    positionCamera = camera->getPosition();
                }
            }
            std::cout << "position";
            std::cout << positionCamera[0] << " " << positionCamera[1] << " " << positionCamera[2];
            for(auto entity : world->getEntities()){
                // Get the street component if it exists
                StreetComponent* street = entity->getComponent<StreetComponent>();
                // If the street component exists
                if(street &&  (entity->localTransform.position[2]-width) >positionCamera[2] ){
                    Entity *newEntity = world->add(); // Make new Entity + Add this Entity to the world
                    entity->localTransform.position[2] -= height * 2;
                }
            }
        }

    };

}
