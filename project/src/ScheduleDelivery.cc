#include "ScheduleDelivery.h"

namespace csci3081 {
    void ScheduleDelivery_Helper::RescheduleDelivery_helper(Package *pack, std::vector<IEntity*>& packages_array, std::vector<IEntity*>& customer_array){
        std::cout << "Package Rescheduled" << std::endl;
        pack->OnSchedule();
        IEntity *cust = dynamic_cast<IEntity*>(pack->GetRecipient());
        IEntity *entity_pack = dynamic_cast<IEntity*>(pack);
        packages_array.push_back(entity_pack);
        customer_array.push_back(cust);
        
    }
    void ScheduleDelivery_Helper::Schedule_Delivery_Entities(std::vector<IEntity*>& entities_, std::vector<IEntity*>& packages_array, std::vector<IEntity*>& customer_array, const IGraph* graph_){
        for (int i = 0; i < entities_.size(); i++) {
            const picojson::object& temp = entities_[i]->GetDetails();
            if (JsonHelper::GetString(temp, "type") == "drone") {
                Drone* nextDrone   = dynamic_cast<Drone*>(entities_[i]);
                bool pass_statement = nextDrone->GetPackage() == nullptr 
                    && nextDrone->DroneAlive()
                    && (packages_array[0]->GetPosition()[1] != -1000 && packages_array[0]->GetPosition()[1] != 264);
        
                if (pass_statement){
                    nextDrone->Scheduled_drone(packages_array[0], customer_array[0], graph_);
                    packages_array.erase(std::remove(packages_array.begin(), packages_array.end(), packages_array[0]), packages_array.end());
                    customer_array.erase(std::remove(customer_array.begin(), customer_array.end(), customer_array[0]), customer_array.end());
                } //close if statement avoiding resceduling multiple times
                    
            }//close if statement for Drone
            if (JsonHelper::GetString(temp, "type") == "robot") {
                Robot* nextRobot   = dynamic_cast<Robot*>(entities_[i]);
                bool pass_statement = nextRobot->GetPackage() == nullptr 
                && nextRobot->RobotAlive()
                && (packages_array[0]->GetPosition()[1] != -1000 && packages_array[0]->GetPosition()[1] != 264);

                if (pass_statement){
                    nextRobot->Scheduled_Robot(packages_array[0], customer_array[0], graph_);
                    std::cout << "size of package array from schedule_robot: " << packages_array.size() << std::endl;
                    packages_array.erase(std::remove(packages_array.begin(), packages_array.end(), packages_array[0]), packages_array.end());
                    customer_array.erase(std::remove(customer_array.begin(), customer_array.end(), customer_array[0]), customer_array.end());
                }//close if statement avoiding resceduling multiple times
            } //close if statement for Robot
        }//close for loop
    }
}