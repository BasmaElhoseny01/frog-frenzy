#pragma once
#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include "../../states/game-over-state.hpp"
#include <imgui.h>

#include <iostream>
using namespace std;
#include "glm/gtx/string_cast.hpp"

namespace our
{
    class LakeSystem
    {
        Application *app;         // The application in which the state runs
        glm::vec3 positionFrog;

    public:
        // This should be called every frame to check on the postion of frog from the lake.
        void update(World *world, ForwardRenderer *forwardRenderer, bool &flagPostProcessing, ISoundEngine *engine)
        {
            // For each entity in the world find the frog
            for (auto entity : world->getEntities())
            {
                if (entity->name == "frog")
                {
                    // get position of frog
                    positionFrog = entity->localTransform.position;
                    break;
                }
            }

            // Check on postion of frog relative to the lakes in the system
            for (auto entity : world->getEntities())
            {
                // Get name of entity
                std::string name = entity->name;
                if (name == "lake")
                {
                    // get the lake's position
                    glm::vec3 lake_position = entity->localTransform.position; // front center of the lake
                    lake_position = lake_position - glm::vec3(0, 0.5, 0);      // for y index modification between grass and lake and frog
                    glm::vec3 lake_size = glm::vec3(20, 0, 10);
                    glm::vec3 lake_max = lake_position + (lake_size);
                    glm::vec3 lake_min = lake_position - (lake_size);
                    // std::cout << "lake_max: " << glm::to_string(lake_max) << std::endl;
                    // std::cout << "lake_min: " << glm::to_string(lake_min) << std::endl;
                    // std::cout << "Frog Position: " << glm::to_string(positionFrog) << std::endl;

                    if (positionFrog.x >= lake_min.x && positionFrog.x <= lake_max.x && positionFrog.y >= lake_min.y && positionFrog.y <= lake_max.y && positionFrog.z >= lake_min.z && positionFrog.z <= lake_max.z)
                    {
                        std::cout << "Lake Position: " << glm::to_string(lake_position) << std::endl;
                        cout << "In Lake" << endl;
                        flagPostProcessing = true;
                        forwardRenderer->setApplyPostProcessing(true);
                        engine->play2D("./media/water.mp3", false);
                    }
                }
            }

            // std::cout << "Frog Position: " << glm::to_string(positionFrog) << std::endl;
        }
        void checkGameOver(bool flagPostProcessing)
        {
            if (flagPostProcessing)
            {
                _sleep(1500);
                app->registerState<GameOver>("game-over");
                app->changeState("game-over");
            }
        }
    };
}