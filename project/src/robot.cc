#include "robot.h"

namespace csci3081 {

	void Robot::Pick_order() {
		package_currently_delivering->OnPickUp(); /// Set the observer pattern to show that package is picked
		currentIndex = 0;
		has_picked_up = true;
		currentRout = pack_to_customer;
		has_delivered_pack = false;
	}//end of function

	void Robot::Drop_order() {
		package_currently_delivering->OnDropOff(); // Set the observer pattern to show that package is picked
		has_picked_up = false;
		package_currently_delivering->SetPosition(Vector3D(0, -1000, 0)); // Set the package position all the way down once it is delivered
		package_currently_delivering = nullptr;
		currentIndex = 0;
		distance_traveled = 0;
		has_delivered_pack = true;
	}//close function 

	void Robot::Dead_Drop_order() {
		float curr_x = package_currently_delivering->GetPosition()[0];
		float curr_z = package_currently_delivering->GetPosition()[2];
		package_currently_delivering->SetPosition(Vector3D(curr_x, 257, curr_z));
	}//close function

	Vector3D  Robot::GetTargetPosition() {
		return Vector3D ( currentRout.at(currentIndex));
	}//close function

	bool Robot::IncrTarget() {
		if (currentIndex+1 == currentRout.size()) {
			return true;
		} //
		currentIndex +=1;
		return false;
	}

	Package* Robot::GetPackage() {
		return package_currently_delivering;
	}

	void Robot::SetPackage(Package* pack) {
		package_currently_delivering = pack;
	}
	bool Robot::RobotAlive(){ // turing coditionals used to return true or false if the robot battery is not dead
		return power_source->GetLevel() > 0 ? true : false;
	}
	bool Robot::Has_delivered_pack(){
		return has_delivered_pack;
	}
	void Robot::SetRobotToPack(std::vector<std::vector<float>> v) {
		Robot_to_pack = v;
	}

	void Robot::SetPackToCustomer(std::vector<std::vector<float>> v) {
		pack_to_customer   = v;
	}

	bool Robot::Within_range(Vector3D v) {
		if (Vector3D (GetPosition()) .DistanceBetween(v) < GetRadius() ) {
			return true;
		}
		else {
			return false;
		}
	}

	float Robot::GetSpeed() {
		return speed;
	}//

	bool Robot::has_picked_up_getter() {
		return has_picked_up;
	}

	void Robot::SetCurrRout(std::string rout) {
		if (rout == "pack") {
		currentRout = Robot_to_pack;
	}
	else if (rout == "customer") {
		currentRout = pack_to_customer;
	}
	}

	void Robot::Update_Package() {
		Vector3D initial_position = Vector3D (package_currently_delivering->GetPosition());
		if (has_picked_up == true) {
			package_currently_delivering->SetPosition(Vector3D (this->GetPosition() ));
			Vector3D temp = Vector3D (package_currently_delivering->GetPosition());
		}
	}

	void Robot::Scheduled_Robot(IEntity* package, IEntity* dest, const IGraph* graph_) {
		if (GetPackage() == nullptr) {
			SetRobotToPack( graph_->GetPath(GetPosition(), package->GetPosition() ) ); // We set the direction path to the package 
			SetPackage(dynamic_cast<Package*>(package)); // need to set the dynamically cast the package to set it to the drone
			SetCurrRout("pack");
			SetPackToCustomer ( graph_->GetPath(package->GetPosition(), dest->GetPosition() )); // We set the direction path to the customer 
			Package* pack = dynamic_cast<Package*>(package); // need to set the dynamically cast the package to set it to the Customer
			pack->SetCustomer(dynamic_cast<Customer*>(dest));
			OnMove();
		} // close  if
	}

	void Robot::update_Robot_movement(float dt) {
		if (GetPackage() != nullptr) {
			if (Within_range(GetTargetPosition())) { // if the drone is within a certain range for performing and action.
				std::cout << "Within Range" << std::endl;
				if (IncrTarget()) {
					if (has_picked_up_getter()) { // if the drone has the package picked
						Drop_order(); // then drop the package to the Customer
						OnIdle(); // and let the drone notify observer that it went Idle mode
					}
					else {
						std::cout << "Picked orders Robot" << std::endl;
						OnIdle(); // initially notify observer that drone went Idle mode
						Pick_order(); // then pick up the order
						OnMove(); // and notify observer that drone is scheduled to move 
					}
				} 
			} 
			else { //we know we have a package 
				Vector3D v = GetTargetPosition()-GetPosition();
				v.Normalize();
				v = v*dt*GetSpeed(); // we calculate the displacement to travel
				power_source->change_level(dt); // we deplete the drone battery level while it is moving
				if (v.Magnitude() > ( Vector3D (GetPosition())- GetTargetPosition() ).Magnitude() ) {
					SetPosition(GetTargetPosition()); // we set the new position listed in the paths vector to the drone as its next position to get to
				}
				else {						
					Vector3D positionToMove = Vector3D ( GetPosition())+v;
					// std::cout << "Robot position" << positionToMove.ToString() << std::endl;
					SetPosition(positionToMove);
				} //close else for overshooting target
				Update_Package(); // we update the package position and its observer status while running the simulation
			} //close else of the within range if
		} //close get package check
	}//close function 

	void Robot::OnIdle() {
		picojson::object obj = JsonHelper::CreateJsonObject();
		JsonHelper::AddStringToJsonObject(obj, "type", "notify");
		JsonHelper::AddStringToJsonObject(obj, "value", "idle");
		const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
		entity_sub->OnEvent(val, *this);
	}

	void Robot::OnMove() {
		picojson::object obj = JsonHelper::CreateJsonObject();
		JsonHelper::AddStringToJsonObject(obj, "type", "notify");
		JsonHelper::AddStringToJsonObject(obj, "value", "moving");
		JsonHelper::AddStdVectorVectorFloatToJsonObject(obj, "path", currentRout);
		const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
		entity_sub->OnEvent(val, *this);
	}

}//close namespace 