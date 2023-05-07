#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {
    class StreetComponent : public Component {
    public:
        // The ID of this component type is "Movement"
        static std::string getID() { return "Street"; }

        // Reads from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}