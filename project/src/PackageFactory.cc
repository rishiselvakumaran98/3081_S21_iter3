#include "PackageFactory.h"

namespace csci3081 {
	// Method checks the picojson of the object and if it is a Package type 
	// the it proceeds to create a Package entity
	IEntity* PackageFactory::CreateEntity(const picojson::object& object) {
		if  (JsonHelper::GetString(object, "type") == "package") {
			std::cout << "Created Package" << std::endl;
			return new Package(object);
		}
		return nullptr;
	} //end function 
} //end namespace 