#pragma once

#include "../ecs/component.hpp"
#include "../shader/shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace our {

   enum class LIGHT_TYPE
   {
       DIRECTIONAL, 
       POINT,
       SPOT

   };


    class LightingComponent : public Component {
    public:
        
        LIGHT_TYPE kind;

        glm::vec3 color = glm::vec3(0, 0, 0); 
        glm::vec3 direction = glm::vec3(0, 0, 0); 
        glm::vec3 attenuation = glm::vec3(0.0f, 0.0f, 0.0f); // indicates the intensity of the light
        // glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);  //for (Directional and Spot)
        glm::vec2 cone_angles = glm::vec2(0.0f, 0.0f);  // for spot light
        
        static std::string getID() { return "Light"; }

        // Reads Light data from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}