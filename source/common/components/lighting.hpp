#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

#define DIRECTIONAL 0
#define POINT       1
#define SPOT        2

namespace our {

    // This component denotes that the MovementSystem will move the owning entity by a certain linear and angular velocity.
    // This component is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/systems/movement.hpp"
    // For a more complex example of how to use the ECS framework, see "free-camera-controller.hpp"
    class LightingComponent : public Component {
    public:

        int kind = 0; 
        glm::vec3 position = {0.0f, 0.0f, 0.0f};
        glm::vec3 direction = {0.0f, 1.0f, 0.0f};
        glm::vec3 color = {1.0f, 1.0f, 1.0f};
        glm::vec3 attenuation = {0.0f, 0.1f, 0.0f};
        glm::vec2 cone_angles = {0.5f*glm::quarter_pi<float>(), 0.5f*glm::half_pi<float>()};

        // The ID of this component type is "Movement"
        static std::string getID() { return "Lighting"; }

        // Reads linearVelocity & angularVelocity from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}