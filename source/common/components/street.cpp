#include "street.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads from the given json object
    void StreetComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
    }
}