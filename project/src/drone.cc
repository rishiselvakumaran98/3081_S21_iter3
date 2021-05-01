#include "drone.h"
#include "Beeline.h"
namespace csci3081 {


void Drone::Pick_order() {
	package_currently_delivering->OnPickUp(); // Set the observer pattern to show that package is picked
	currentIndex = 0;
	has_picked_up = true;
	currentRout = pack_to_customer;
	has_delivered_pack = false;
}//end of function

void Drone::Drop_order() {
	package_currently_delivering->OnDropOff(); // Set the observer pattern to show that package is picked
	has_picked_up = false;
	package_currently_delivering->SetPosition(Vector3D(0, -1000, 0)); // Set the package position all the way down once it is delivered
	package_currently_delivering = nullptr;
	currentIndex = 0;
	distance_traveled = 0;
	has_delivered_pack = true;
}//close function 

void Drone::Dead_Drop_order() {
	float curr_x = package_currently_delivering->GetPosition()[0];
	float curr_z = package_currently_delivering->GetPosition()[2];
	package_currently_delivering->SetPosition(Vector3D(curr_x, 257, curr_z));
}//close function

Vector3D  Drone::GetTargetPosition() {
	return Vector3D ( currentRout.at(currentIndex) );
}//close function

bool Drone::IncrTarget() {
	if (currentIndex+1 == currentRout.size()) {
		return true;
	} //
	currentIndex +=1;
	return false;
}

Package* Drone::GetPackage() {
	return package_currently_delivering;
}

void Drone::SetPackage(Package* pack) {
	package_currently_delivering = pack;
}
bool Drone::DroneAlive(){
	if (power_source->GetLevel() <= 0){
		if (dead_count == 0){ 
			OnIdle(); // this is done to make sure that observer is notified once of the drone being dead
		}dead_count++; // This variable is incremented to stop the OnIdle from being called multiple times
		has_delivered_pack = false;
		return false;
	}
	return true;
}
bool Drone::Has_delivered_pack(){
	return has_delivered_pack;
}

void Drone::SetDroneToPack(std::vector<std::vector<float>> v) {
	drone_to_pack = v;
}

void Drone::SetPackToCustomer(std::vector<std::vector<float>> v) {
	pack_to_customer   = v;
}

bool Drone::Within_range(Vector3D v) {
	if (Vector3D (GetPosition()) .DistanceBetween(v) < GetRadius() ) {
		return true;
	}
	else {
		return false;
	}
}

float Drone::GetSpeed() {
	return speed;
}//

bool Drone::has_picked_up_getter() {
	return has_picked_up;
}

void Drone::SetCurrRout(std::string rout) {
	if (rout == "pack") {
	currentRout = drone_to_pack;
}
else if (rout == "customer") {
	currentRout = pack_to_customer;
}
}

void Drone::Update_Package() {
	Vector3D initial_position = Vector3D (package_currently_delivering->GetPosition());
	if (has_picked_up == true) {
		package_currently_delivering->SetPosition(Vector3D (this->GetPosition() ));
		Vector3D temp = Vector3D (package_currently_delivering->GetPosition());
	}
}

void Drone::Scheduled_drone(IEntity* package, IEntity* dest, const IGraph* graph_) {
	if (GetPackage() == nullptr) {
		strategy->SetGraph(graph_);
		SetDroneToPack(strategy->GetPath(GetPosition(),  package->GetPosition())); // We set the direction path to the package 
		SetPackage(dynamic_cast<Package*>(package)); // need to set the dynamically cast the package to set it to the drone
		SetCurrRout("pack");
		SetPackToCustomer ( strategy->GetPath(package->GetPosition(), dest->GetPosition() )); // We set the direction path to the customer 
		Package* pack = dynamic_cast<Package*>(package); // need to set the dynamically cast the package to set it to the Customer
		pack->SetCustomer(dynamic_cast<Customer*>(dest));
		package_currently_delivering->OnSchedule();
		OnMove();
	}// close  if
}

void Drone::update_drone_movement(float dt) {
	if (GetPackage() != nullptr && GetPackage() != NULL) {
		if (Within_range(GetTargetPosition())) { // if the drone is within a certain range for performing and action.
			if (IncrTarget()) {
				if (has_picked_up_getter()) { // if the drone has the package picked
					Drop_order(); // then drop the package to the Customer
					OnIdle(); // and let the drone notify observer that it went Idle mode
				}
				else {
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
			if (v.Magnitude() > ( Vector3D (GetPosition() )- GetTargetPosition() ).Magnitude() ) {
				this->SetPosition(GetTargetPosition()); // we set the new position listed in the paths vector to the drone as its next position to get to
			} 
			else {						
				Vector3D positionToMove = Vector3D ( GetPosition())+v; // we then set the next calculated position for the drone to move 
				this->SetPosition(positionToMove);
			} 
			Update_Package(); // we update the package position and its observer status while running the simulation
		} //close else of the within range if
	} //close get package check
}//close function 

void Drone::OnIdle() {
	picojson::object obj = JsonHelper::CreateJsonObject();
	JsonHelper::AddStringToJsonObject(obj, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj, "value", "idle");
	const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
	entity_sub->OnEvent(val, *this);
}

void Drone::OnMove() {
	picojson::object obj = JsonHelper::CreateJsonObject();
	JsonHelper::AddStringToJsonObject(obj, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj, "value", "moving");
	JsonHelper::AddStdVectorVectorFloatToJsonObject(obj, "path", currentRout);
	const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
	entity_sub->OnEvent(val, *this);
}
void Drone::helper_Create_Strategy(const picojson::object details) {
	if (JsonHelper::GetString(details, "path") == "beeline"){
		strategy = new Beeline();
	}
	else if(JsonHelper::GetString(details, "path") == "parabolic"){
		strategy = new Parabolic();
	}
	else if(JsonHelper::GetString(details, "path") == "smart"){
		strategy = new Smart();
	}

}//close helper

}//close namespace 