#include "Battery.h"
#include <iostream>


namespace csci3081 {

	bool Battery::Is_dead() {
		// We check if the battery is dead and if so,
		// return true else false
		if (battery_level == 0) {
			return true;
		}
		return false;
	}

	float Battery::GetLevel() {
		return battery_level;
	}

	void Battery::change_level(float delta) {
		battery_level -= delta;
	}//end of function

	bool Battery::Is_charged() {
		// if battery is at max capacity at 10000 secs
		// then return true else false
		if (battery_level == 10000) {
			return true;
		}
			return false;
		}

}//end of namespace 
