#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    // This component denotes that the HeartComponent will check if player has anther opportunity
    // This component is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/systems/Heart.hpp"
    // For a more complex example of how to use the ECS framework, see "free-camera-controller.hpp"
    class HeartComponent : public Component {
    public:
        int id; // id for heart
        // The ID of this component type is "Heart"
        static std::string getID() { return "Heart"; }

        // Reads linearVelocity & angularVelocity from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}