#include "scope.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our
{
    // Reads size from the given json object
    void ScopeComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        component_size = data.value("size", component_size);
    }
}