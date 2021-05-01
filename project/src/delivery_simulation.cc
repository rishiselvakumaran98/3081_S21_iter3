#include "delivery_simulation.h"
#include "entity_base.h"
#include "json_helper.h"
#include "drone.h"


namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	comp_fact = CompositeFactory();
	AddFactory(new DroneFactory());
	AddFactory(new RobotFactory());
	AddFactory(new PackageFactory());
	AddFactory(new CustomerFactory());
	sing = SingletonCSV::GetSingleton();
	sing->CleanFile("beeline_drone.csv");
	sing->WriteStandardTitleToCSV("beeline_drone.csv");
}

DeliverySimulation::~DeliverySimulation() {}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
		IEntity* temp =  comp_fact.CreateEntity(val);
		if (temp != nullptr) {
			EntityBase* tempBase = dynamic_cast<EntityBase*>(temp);
			tempBase->SetId(NewId());
			tempBase->SetIsub(&isub);
			return tempBase;
		}//close if
		return nullptr;
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	comp_fact.AddFactory(factory);
}

void DeliverySimulation::AddEntity(IEntity* entity) { 
	if (dynamic_cast<Drone*>(entity)) {
		std::cout << "Added Drone" << std::endl;
	} else if (dynamic_cast<Robot*>(entity)) {
		std::cout << "Added Robot" << std::endl;
	} else if (dynamic_cast<Package*>(entity)) {
		std::cout << "Added Package" << std::endl;
	} else if (dynamic_cast<Customer*>(entity)) {
		std::cout << "Added Customer" << std::endl;
	}
	entities_.push_back(entity);
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	graph_ = graph;
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	packages_array.push_back(package);
	customer_array.push_back(dest);
}//close function

void DeliverySimulation::ActualScheduleDelivery(){
	// calls on the Schedule_Delivery_Entities method in ScheduleDelivery to schedule delivery for entities
	deliverer->Schedule_Delivery_Entities(entities_, packages_array, customer_array, graph_);
}
void DeliverySimulation::RescheduleDelivery(Package* pack){
	// calls on the RescheduleDelivery_helper method in ScheduleDelivery to reschedule delivery
	deliverer->RescheduleDelivery_helper(pack, packages_array, customer_array);
	ActualScheduleDelivery();
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {
	isub.AddObserver(observer);
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
	isub.RemoveObserver(observer);
}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {
	ActualScheduleDelivery();
	dt_temp += dt;
	for (int i = 0; i < entities_.size(); i++) {
		const picojson::object& temp = entities_[i]->GetDetails();
		if (JsonHelper::GetString(temp, "type") == "drone") {
			Drone* nextDrone   = dynamic_cast<Drone*>(entities_[i]);
			if (nextDrone->DroneAlive()){
				nextDrone->update_drone_movement(dt);
				float battery = nextDrone->GetBattery()->GetLevel();
				sing->WritePositionToCSV("beeline_drone.csv", nextDrone->GetPosition(), dt_temp, battery);
			}
			else if (drone_rescheduleCount == 0){ // if the drone battery is dead and avoid keep calling the method repetitedly
				// If the drone is carrying Package drop the package to the ground
				if (nextDrone->has_picked_up_getter()) nextDrone->Dead_Drop_order();
				RescheduleDelivery(nextDrone->GetPackage());
				drone_rescheduleCount++;
			} 
		} //close type check for entity
		if (JsonHelper::GetString(temp, "type") == "robot") {
			Robot* nextRobot   = dynamic_cast<Robot*>(entities_[i]);
			if (nextRobot->RobotAlive()){
				nextRobot->update_Robot_movement(dt);
			}
			else if (robot_rescheduleCount == 0) { // if the robot battery is dead and avoid keep calling the method repetitedly
				// If the Robot is carrying Package drop the package to the ground
				if (nextRobot->has_picked_up_getter()) nextRobot->Dead_Drop_order();
				RescheduleDelivery(nextRobot->GetPackage());
				robot_rescheduleCount++;
			}
		} //close type check for entity
	} //close for loop
} //end function

// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {

	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
