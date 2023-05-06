#include "car.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

#include <iostream>
using namespace std;

namespace our
{
    // Reads carComponent from the given json object
    void CarComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        hidden = data.value("hidden", hidden);
        renderEvery = data.value("renderEvery", renderEvery);
        lifeTime = data.value("lifeTime", lifeTime);
        time(&renderTime); // Used only if the component isn't by default hidden :D else this is dummy
        start_x = data.value("start_x", start_x);

        // cout << "Car Deserialize :D" << endl;
        // cout << "start_time" << renderTime << endl;
        // cout << "lifeTime :D" << lifeTime << endl;
    }
}