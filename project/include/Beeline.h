/**
 *@file beeline.h
 */

#ifndef BEELINE_H_
#define BEELINE_H_

/**
 * include
 */
#include "Vector3D.h"
#include <vector>
#include "IStrategy.h"

namespace csci3081 {
	/**
	 * @brief this class inhertis from the IStrategy class and is responsible for generating the beeline that the drone will take.
	 */
	class Beeline : public IStrategy {
		public:
			/**
			 * @brief The GetPath method inhertied from the IStrategy class get overriden to provide coordinates for the beeline path.
			 * @param[In] source: an std::vector<float> that represents the starting point of the path to be be generated.
			 * @param[In] destination: an std::vector<float> that represents the vertex that we need to reach by taking this path.
			 * @return this method returns a nested vector float that represents the path from the starting point to the destination.Each vector in this nested vector represents a point where the drone changes directions.
			 */
			std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination);
	}; //end class
} //close namespace csci3081
#endif // BEELINE_H_