/**
 *@file Istrategy.h
 */
#ifndef ISTRATEGY_H_
#define ISTRATEGY_H_
/**
 * include
 */
#include <EntityProject/facade/delivery_system.h>
#include <vector>

namespace csci3081 {
	/**
	 * @brief An abstract class that represents the three different paths that the drone can take to reach its desired destination.
	 */
	class IStrategy {
		public:
			/**
			 * @brief this method calculated the path to be taken by the drone.
			 * @param[In] source: an std::vector<float> that represents the starting point of the path to be be generated.
			 * @param[In] destination: an std::vector<float> that represents the vertex that we need to reach by taking this path.
			 * @return this method returns a nested vector float that represents the path from the starting point to the destination.Each vector in this nested vector represents a point where the drone changes directions.
			 */
			virtual std::vector<std::vector<float>> GetPath(std::vector<float> source, std::vector<float> destination) = 0;
			/**
			 * @brief a simple setter method that sets the current IGraph object to be used to set the graph of the simulation.
			 * @param[In] graph: An IGraph object to be used to generate the path for this simulation.
			 * @return this method is void. It does not return anything.
			*/
			void SetGraph(const IGraph* graph_) { graph = graph_; };
		protected:
			// IGraph object to be used in the simulation.
			const IGraph* graph;
	}; //close class 
// namespace csci3081
}

#endif // ISTRATEGY_H_