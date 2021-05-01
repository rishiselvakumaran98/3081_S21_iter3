#include "Beeline.h"
namespace csci3081 {

    std::vector<std::vector<float>> Beeline::GetPath(std::vector<float> source, std::vector<float> destination) {
        std::vector<std::vector<float>> path;
        source[1] += 200; // We add 200 points to the initial y-position to let the drone fly higher initially
        destination[1] += 200; // We add 200 points to the destination y-position to let maintain the straight path of drone
        path.push_back(source);
        path.push_back(destination);
        destination[1] -= 200; // We reconfigure the destination position for the drone to land
        path.push_back(destination);
        return path;
    }

} //close namespace 