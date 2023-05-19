#include "lighting.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {

    void LightingComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        kind = data.value("kind", kind);
        position = data.value("position", position);
        direction = data.value("direction", direction);
        color = data.value("color", color);
        attenuation = data.value("attenuation", attenuation);
        cone_angles = glm::radians(data.value("cone_angles", cone_angles));
    }
}