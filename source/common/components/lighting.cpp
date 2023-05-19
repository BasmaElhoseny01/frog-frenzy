#include "lighting.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <asset-loader.hpp>
#include "../deserialize-utils.hpp"
namespace our
{

    // Reads light from the given json object
    void LightingComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())return;
        int kind = data.value("kind", 0);  // read the type of the light and set the default to be directional.

        color = glm::vec3(data.value("color", glm::vec3(1, 0.9, 0.7)));
        attenuation = glm::vec3(data.value("attenuation", glm::vec3(1, 0, 0)));
        direction = glm::vec3(data.value("direction", glm::vec3(0, -1, 0)));
        // cone_angles = glm::vec2(data.value("cone_angles", glm::vec2(glm::radians(90.0f), glm::radians(120.0f))));
        cone_angles.x = glm::radians((float)data.value("cone_angles.inner",90));
        cone_angles.y = glm::radians((float)data.value("cone_angles.outer",120));
    }

}