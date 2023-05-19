#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    // This component denotes that the CollisionComponent has dimensions to know collision 
    // This component is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/systems/collision.hpp"
    // For a more complex example of how to use the ECS framework, see "free-camera-controller.hpp"
    class CollisionComponent : public Component {
    public:
         glm::vec3 size; // size for car
        // The ID of this component type is "Collision"
        static std::string getID() { return "Collision"; }

        // Reads linearVelocity & angularVelocity from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}