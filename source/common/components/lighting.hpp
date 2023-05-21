#pragma once

#include "../ecs/component.hpp"
#include "../shader/shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace our {
    // create light class from component class
    // with initial value for parameters 
    class LightingComponent : public Component {
    public:
        
        int kind;

        glm::vec3 diffuse = glm::vec3(0, 0, 0); 
        glm::vec3 specular = glm::vec3(0, 0, 0); 
        glm::vec3 direction = glm::vec3(0, 0, 0); 
        glm::vec3 position = glm::vec3(0, 0, 0); 
        glm::vec3 attenuation = glm::vec3(0.0f, 0.0f, 0.0f); // indicates the intensity of the light
        glm::vec2 cone_angles = glm::vec2(0.0f, 0.0f);  // for spot light
        // return the id
        static std::string getID() { return "Lighting"; }

        // Reads Light data from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}