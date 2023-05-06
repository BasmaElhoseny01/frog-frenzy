#pragma once

#include "../ecs/component.hpp"

#include <glm/mat4x4.hpp>
#include <chrono>
#include <ctime>

namespace our
{

    // Car Component
    class CarComponent : public Component
    {
    public:
        // life time for the car to be appearing
        bool hidden = false;
        int renderEvery = 0;
        double lifeTime = 0;
        time_t renderTime;
        int start_x = 0;

        // The ID of this component type is "Car"
        static std::string getID() { return "Car"; }

        // Reads camera parameters from the given json object
        void deserialize(const nlohmann::json &data) override;
    };

}