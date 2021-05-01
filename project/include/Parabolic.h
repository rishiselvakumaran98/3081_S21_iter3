/**
 *@file Parabolic.h
 */

#ifndef PARABOLIC_H_
#define PARABOLIC_H_

/**
 * include
 */
#include "IStrategy.h"
#include <vector>
#include "Vector3D.h"
#include <cmath>

namespace csci3081 {
	/**
	 * @brief This class inherites from the IStrategy class. It provides the drone with the parabolic path.
	 */
	class Parabolic : public IStrategy {
		public:
			/**
			 * @brief The GetPath method that formulates the coordinates for the Parabolic movement of the drone.
			 * @param[In] source: an std::vector<float> that represents the starting point of the path to be be generated.
			 * @param[In] destination: an std::vector<float> that represents the vertex that we need to reach by taking this path.
			 * @return this method returns a nested vector float that represents the path from the starting point to the destination.Each vector in this nested vector represents a point where the drone changes directions.
			 */
			std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination); 
		}; //close class
} //end of namespace 
// namespace csci3081
#endif // PARABOLIC_H_