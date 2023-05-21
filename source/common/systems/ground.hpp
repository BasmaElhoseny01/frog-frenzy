#pragma once
#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include "../components/movement.hpp"

namespace our
{
    // The Ground System is responsible for rendering the forward entities by increasing their z index to go more deeper
    // This system is added as a simple example for how use the ECS framework to implement logic.
    class GroundSystem
    {
        glm::vec4 positionCamera;
        int width = 20;
        int height = 40; // Height by which we inc the depth

    public:
        // This should be called every frame to update all entities containing a StreetComponent.
        void update(World *world, int &score)
        {
            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // Get the camera component if it exists
                CameraComponent *camera = entity->getComponent<CameraComponent>();
                // If the street component exists
                if (camera)
                {
                    positionCamera = camera->getPosition();
                }
            }
            for (auto entity : world->getEntities())
            {
                // Get name of entity
                std::string name = entity->name;
                // If the street or grass or lake components exists inc the score as the frog moves forward
                if ((name == "street" || name == "grass" || name == "lake") && (entity->localTransform.position[2] - width) > positionCamera[2])
                {
                    score++; // inc score
                    for (auto entity2 : world->getEntities())
                    {
                        // Loop to render cars and taxis and lamps ... to the forward :D
                        if ((entity2->name == "car" || entity2->name == "taxi" || entity2->name == "fence" || entity2->name == "wall" || entity2->name == "hole" || entity2->name == "point_lamp" || entity2->name == "spot_lamp") && (entity2->localTransform.position[2]) > (entity->localTransform.position[2] - width / 2))
                        {
                            // change taxi or bus position
                            entity2->localTransform.position[2] -= height * 4;
                            // check if car or not
                            MovementComponent *move = entity2->getComponent<MovementComponent>();
                            if (move)
                            {
                                // Increase speed of the cars as the frog moves more to the front
                                int xSpeed = move->linearVelocity.x;
                                // inc speed of car
                                move->linearVelocity.x += (xSpeed < 0) ? -5 : 5;
                            }
                        }
                    }
                    // change grass or street position
                    entity->localTransform.position[2] -= height * 4;
                }
                else if (name == "heart gain" && (entity->localTransform.position[2] - width) > positionCamera[2])
                {
                    //If the heart isn't taken before then rerender it
                    int x_old = entity->localTransform.position[0];
                    int x_rand = 0 + (std::rand() % (35 + 1)); // random number from 0-35
                    if (x_old > 0)
                    {
                        x_rand *= -1;
                    }
                    entity->localTransform.position[0] += x_rand;
                    // change z [60-100]
                    int z_rand = 60 + (std::rand() % (100 + 1 - 60));
                    entity->localTransform.position[2] -= z_rand;
                }
            }
        }
    };

}
