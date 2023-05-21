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
        kind = data.value("kind", 0);  // read the type of the light and set the default to be directional.

        diffuse = glm::vec3(data.value("diffuse", glm::vec3(1, 0.9, 0.7))); // read the diffuse of the light and set the default 
        specular = glm::vec3(data.value("specular", glm::vec3(1, 0.9, 0.7)));// read the specular of the light and set the default 
        attenuation = glm::vec3(data.value("attenuation", glm::vec3(1, 0, 0)));// read the attenuation of the light and set the default 
        direction = glm::vec3(data.value("direction", glm::vec3(0, -1, 0)));// read the direction of the light and set the default 
        position = glm::vec3(data.value("position", glm::vec3(0, 0, 0)));// read the direction of the light and set the default 
        cone_angles.x = glm::radians((float)data.value("cone_angles.inner",90));// read the cone_angles.inner of the light and set the default
        cone_angles.y = glm::radians((float)data.value("cone_angles.outer",120));// read the cone_angles.outer of the light and set the default
    }

}