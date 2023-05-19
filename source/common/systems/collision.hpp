#pragma once
#include "../ecs/world.hpp"
#include "../components/heart.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include "../../states/game-over-state.hpp"
#include "../../states/play-state.hpp"
#include "../ecs/entity.hpp"

namespace our
{

    class CollisionSystem {
        Application *app;         // The application in which the state runs
        glm::vec3 positionFrog;
        int width = 20;
        int height = 40;
        vector<Entity> cars;
        Entity *heartEntity = nullptr;
        Entity *frog = nullptr;
    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }
        // This should be called every frame to update all entities containing a StreetComponent.
        void update(World* world,ForwardRenderer *forwardRenderer, bool& flagPostProcessing,ISoundEngine *engine,int& id) {
            // For each entity in the world
            for(auto entity : world->getEntities()){
                if (entity->name=="frog")
                {
                    // get position of frog
                    positionFrog = entity->localTransform.position;
                    frog = entity;
                    break;
                }
            }
            bool flag = false;

            HeartComponent *heart = nullptr;
            for(auto entity : world->getEntities()){
                // Get name of entity
                std::string name = entity->name;
                // get the car's position
                glm::vec3 car_position = entity->localTransform.position;
                // If the bus or taxi component exists
                heart = entity->getComponent<HeartComponent>();
                if(heart && heart->id==id){
                    heartEntity = entity;
                }
                if((name=="bus")){
                    // get the car's max and min position
                    glm::vec3 bus_size =  glm::vec3(13, 0, 3);
                    glm::vec3 car_max = car_position + (bus_size  );
                    glm::vec3 car_min = car_position - (bus_size );
                    if (positionFrog.x >= car_min.x && positionFrog.x <= car_max.x &&
                            positionFrog.y >= car_min.y && positionFrog.y <= car_max.y &&
                            positionFrog.z >= car_min.z && positionFrog.z <= car_max.z)
                        {
                            flag = true;
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
                            flag = true;
                        }
                }
            }
            if(flag){
                if(id==2){
                    flagPostProcessing = true;
                    forwardRenderer->setApplyPostProcessing(true);
                }else{
                    heartEntity->localTransform.position[1] = 100;
                    frog->localTransform.position[2] -= height;
                }
                engine->play2D("./media/scream.mp3", false);
                id++;
            }
        }

        void checkGameOver(bool flagPostProcessing){
            if(flagPostProcessing){
                _sleep(1500);
                app->registerState<GameOver>("game-over");
                app->changeState("game-over");
                // app->registerState<Playstate>("play");
                // app->changeState("play");
            }
        }
        void exit(){
           
        }

    };

}
