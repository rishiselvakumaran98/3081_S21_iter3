/**
 *@file Smart.h
 */

#ifndef SMART_H_
#define SMART_H_

/**
 * include
 */
#include "IStrategy.h"

namespace csci3081 {
	/**
	 * @brief This class inherites from the IStrategy class. It provides the drone with the smart path that it can take.
	 */
	class Smart : public IStrategy  {
		public:
			/**
			 * @brief The GetPath method inhertied from the IStrategy class get overriden to provide coordinates for the Smart path.
			 * @param[In] source: an std::vector<float> that represents the starting point of the path to be be generated.
			 * @param[In] destination: an std::vector<float> that represents the vertex that we need to reach by taking this path.
			 * @return this method returns a nested vector float that represents the path from the starting point to the destination.Each vector in this nested vector represents a point where the drone changes directions.
			 */
			std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination);
		}; //close class
}//close namespace csci3081
#endif // SMART_H_
