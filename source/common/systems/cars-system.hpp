#pragma once

#include "../ecs/world.hpp"
#include "../components/car.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <unordered_set>

namespace our
{

    // The Car System system is responsible for Appearing and Disappearing of cars
    // This system is added as a simple example for how use the ECS framework to implement logic.
    class CarsSystem
    {
    public:
        // This should be called every frame to update all entities containing a MovementComponent.
        void update(World *world)
        {
            time_t time_now;
            time(&time_now);
            // Add Entities to be hidden in this list

            // time_t time_now;
            // time(&time_now);
            // // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // FIXME: Get the car components if it exists [Hides and appears in general :D]
                CarComponent *car = entity->getComponent<CarComponent>();
                if (car)
                {
                    // Hide this entity from the world
                    if (car->hidden == true || double(time_now - car->renderTime) > car->lifeTime)
                    {
                        // 1.Take a copy from this entity [Deep copy] VIP
                        // Entity *hiddenEntity = new Entity(*entity);
                        // 2.Add this entity to the hiddenEntities set
                        // 3.Delete from the world
                        world->markToHide(entity);
                    }
                }
            }

            // UnHide Entities
            for (auto entity : world->getHiddenEntities())
            {
                CarComponent *car = entity->getComponent<CarComponent>();
                if (car)
                {
                    if (time_now % car->renderEvery == 0)
                    {
                        // cout << "Basma" << endl;
                        car->hidden = false;
                        // Update Render time to be now
                        time(&(car->renderTime));
                        entity->localTransform.position[0] = car->start_x; // The position is defined as a vec3. (0,0,0) means no translation
                        world->markToUnhide(entity);
                    }
                }
            }

            // Hide and Unhide Marked Entities :D
            world->hideMarkedEntities();
            world->unhideMarkedEntities();

            // cout << "World Entities" << world->getEntities().size() << endl;
            // cout << "Removal Entities" << world->getmarkedForRemoval().size() << endl;
            // cout << "Hidden Entities" << world->getHiddenEntities().size() << endl;
        }
    };

}
