#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    // This component denotes that Component has a scope to be used in the Collision.
    // This component is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/systems/movement.hpp"
    // For a more complex example of how to use the ECS framework, see "free-camera-controller.hpp"
    class ScopeComponent : public Component {
    public:
        glm::vec3 component_size = {0, 0, 0}; //The size of the component to be used as its scope for collision

        // The ID of this component type is "Movement"
        static std::string getID() { return "Scope"; }

        // Reads linearVelocity & angularVelocity from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}