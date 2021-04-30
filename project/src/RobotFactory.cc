#include "RobotFactory.h"

namespace csci3081 {
	// Method checks the picojson of the object and if it is a Robot type 
	// the it proceeds to create a Robot entity
	IEntity* RobotFactory::CreateEntity(const picojson::object& object) {
		if  (JsonHelper::GetString(object, "type") == "robot") {
			std::cout << "Created Robot" << std::endl;
			return new Robot(object);
		}
		return nullptr;
	} //end function 
} //end namespace 