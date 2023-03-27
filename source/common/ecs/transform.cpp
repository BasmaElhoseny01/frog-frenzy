#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>


namespace our {

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const {
        //TODO: (Req 3) Write this function
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
        // here we create the translate matrix given the position
        glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale);
        // here we create the scale matrix
        glm::mat4 rotate = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
        // here we create the rotation matrix
        
        glm::mat4 transform = translate * rotate * scaling;
        // we got the transform out of multiplication of the three matrices TRS
        // in the following order so that the vector is got scaled first 
        // then rotated and finally translated to the position

        return transform; 
    }

     // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json& data){
        position = data.value("position", position);
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));
        scale    = data.value("scale", scale);
    }

}