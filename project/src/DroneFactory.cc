#include "DroneFactory.h"

namespace csci3081 {
	// Method checks the picojson of the object and if it is a Drone type 
	// the it proceeds to create a Drone entity
	IEntity* DroneFactory::CreateEntity(const picojson::object& object) {
		if  (JsonHelper::GetString(object, "type") == "drone") {
			std::cout << "Created Drone" << std::endl;
			return new Drone(object);
		}
		return nullptr;
	} //end function 
} //end namespace 