#include "CustomerFactory.h"

namespace csci3081 {
	// Method checks the picojson of the object and if it is a Customer type 
	// the it proceeds to create a Customer entity
	IEntity* CustomerFactory::CreateEntity(const picojson::object& object) {
		if  (JsonHelper::GetString(object, "type") == "customer") {
			std::cout << "Created Customer" << std::endl;
			return new Customer(object);
		}
		return nullptr;
	} //end function 
} //end namespace 