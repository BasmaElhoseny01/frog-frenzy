#pragma once

#include "../ecs/world.hpp"
#include "../components/free-frog-controller.hpp"

#include "../application.hpp"
#include "../components/mesh-renderer.hpp"
#include "../components/free-frog-controller.hpp"
#include "../components/camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // The free frog controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-frog-controller.hpp"
    class FreeFrogControllerSystem
    {
        Application *app;         // The application in which the state runs
        bool mouse_locked = true; // Is the mouse locked

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }

        // This should be called every frame to update all entities containing a FreeFrogControllerComponent
        void update(World *world, float deltaTime, ForwardRenderer *forwardRenderer)
        {
            // First of all, we search for an entity containing both a MeshRendererComponent and a FreeFrogControllerComponent
            // As soon as we find one, we break
            // MeshRendererComponent *MeshRenderer = nullptr;
            FreeFrogControllerComponent *controller = nullptr;
            CameraComponent *camera = nullptr;
            for (auto entity : world->getEntities())
            {
                // MeshRenderer = entity->getComponent<MeshRendererComponent>();
                controller = entity->getComponent<FreeFrogControllerComponent>();
                camera = entity->getComponent<CameraComponent>();

                if (camera && controller)
                    break;
            }

            // If there is no entity with both a MeshRendererComponent and a FreeFrogControllerComponent, we can do nothing so we return
            if (!(controller && camera))
                return;

            // Get the entity that we found via getOwner (we could use controller->getOwner())
            Entity *entity = controller->getOwner();

            // We get a reference to the entity's position and rotation [camera]
            glm::vec3 &positionCamera = entity->localTransform.position;
            glm::vec3 &rotationCamera = entity->localTransform.rotation;

            // We get a reference to the entity's position and rotation [frog]
            glm::vec3 &positionFrog = entity->parent->localTransform.position;
            glm::vec3 &rotationFrog = entity->parent->localTransform.rotation;

            // We get the camera model matrix (relative to its parent) to compute the front, up and right directions
            glm::mat4 matrix = entity->parent->localTransform.toMat4();

            glm::vec3 front = glm::vec3(matrix * glm::vec4(0, 0, -1, 0)),
                      up = glm::vec3(matrix * glm::vec4(0, 1, 0, 0)),
                      right = glm::vec3(matrix * glm::vec4(1, 0, 0, 0));

            glm::vec3 current_sensitivity = controller->positionSensitivity;

            // If the LEFT SHIFT key is pressed, we multiply the position sensitivity by the speed up factor
            if (app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT))
                current_sensitivity *= controller->speedupFactor;
            // left
            if (app->getKeyboard().isPressed(GLFW_KEY_A) || app->getKeyboard().isPressed(GLFW_KEY_LEFT))
            {

                // positionFrog -= right * (deltaTime * current_sensitivity.x);

                positionFrog += up * (deltaTime * current_sensitivity.y);
                rotationFrog.y = glm::half_pi<float>();
                rotationCamera.x = 0;
                rotationCamera.y = -0.5 * glm::half_pi<float>();
                rotationCamera.z = -glm::half_pi<float>();
                positionCamera.x = -75;
                positionCamera.y = 0;
                positionCamera.z = 150;
                // rotationCamera.z = -90;
            }
            // right
            if (app->getKeyboard().isPressed(GLFW_KEY_D) || app->getKeyboard().isPressed(GLFW_KEY_RIGHT))
            {
                // positionFrog += right * (deltaTime * current_sensitivity.x);
                positionFrog += up * (deltaTime * current_sensitivity.y);
                rotationFrog.y = -glm::half_pi<float>();
                rotationCamera.x = 0;
                rotationCamera.y = 0.5 * glm::half_pi<float>();
                rotationCamera.z = glm::half_pi<float>();
                positionCamera.x = 75;
                positionCamera.y = 0;
                positionCamera.z = 150;
            }
            // forward
            if (app->getKeyboard().isPressed(GLFW_KEY_W) || app->getKeyboard().isPressed(GLFW_KEY_UP))
            {
                positionFrog += up * (deltaTime * current_sensitivity.y);
                rotationFrog.y = 0;
                rotationCamera.y = glm::pi<float>();
                rotationCamera.x = (3.0 / 4) * glm::pi<float>();
                rotationCamera.z = glm::pi<float>();
                positionCamera.x = 0;
                positionCamera.y = -75;
                positionCamera.z = 150;

                // Apply GreyPost Processing
                forwardRenderer->setApplyPostProcessing(true);
            }
        }

        // When the state exits, it should call this function to ensure the mouse is unlocked
        void exit()
        {
        }
    };

}
