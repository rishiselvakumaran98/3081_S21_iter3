#ifndef BEELINE_H_
#define BEELINE_H_


#include "Vector3D.h"
#include <vector>
#include "IStrategy.h"

namespace csci3081 {
	class Beeline : public IStrategy {
		public:
			/**
			 * @brief The GetPath method that formulates the coordinates for the Beeline movement of the drone
			 */
			std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination);
		}; //end class
} //close namespace 

#endif