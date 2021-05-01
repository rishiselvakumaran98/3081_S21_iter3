/**
 * @file drone.h
 */
#ifndef DRONE_H_
#define DRONE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>
#include <string>
#include "Package.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Battery.h"
#include "IStrategy.h"
#include "Beeline.h"
#include "Parabolic.h"
#include "Smart.h"
namespace csci3081 {
   	/*******************************************************************************
    * Class Definitions
    ******************************************************************************/
   	/**
    * @brief These are the methods that will be used for the drone class.
    *
    * This class will have functions that control a drone, pick up and drop off packages. Also, private fields for keep track of the speed and other variables relevant to a drone.
    */
	class Drone : public csci3081::EntityBase {

		public:
			/**
			 *  @brief basic constructor for a drone object. Taking a picojson object that received from entity base.
			 * @param details_ the picojson from the facade to be used as a setup for the entity
			*/
			Drone(const picojson::object& details_):csci3081::EntityBase(details_) {
				details = details_;
				package_currently_delivering = nullptr;
				speed = JsonHelper::GetDouble(details_, "speed");
				has_picked_up = false;
				distance_traveled = 0;
				float battery_capacity;
				if(JsonHelper::ContainsKey(details_, "battery_capacity")){
					battery_capacity = JsonHelper::GetDouble(details_, "battery_capacity");
				// if (battery_capacity < 200) battery_capacity = 3000;
				}
				else
					battery_capacity = 10000;
				power_source = new Battery(battery_capacity, "xc");
				has_delivered_pack = false;
				if (!JsonHelper::ContainsKey(details_, "path"))
					JsonHelper::AddStringToJsonObject(details, "path", "smart");
				helper_Create_Strategy(details);
			}
			

			/**
			 * @brief more complex constructor for drones
			 * @param s s-value for speed of the drone
			 * @param b pointer to a Battery to be implemented on the drone
			 * @param details_ the picojson from the facade 
			 */
			Drone(float s, Battery* b, const picojson::object& details_):EntityBase(details_) {
				speed = s;
				power_source = b;
				details = details_;
				package_currently_delivering = nullptr;
				has_picked_up = false;
				distance_traveled = 0;
				if (!JsonHelper::ContainsKey(details_, "path"))
					JsonHelper::AddStringToJsonObject(details, "path", "smart");
				helper_Create_Strategy(details);
			}//close constructor 

			/**
			 * @brief another constructor for drones
			 * @param p the vector float to be used as the position of the drone 
			 * @param d the direction float vector of the drone
			 * @param details the picojson object form the facade 
			 */
			Drone(std::vector<float> p, std::vector<float> d, const picojson::object& details_):EntityBase(details_) {
				position = p;
				direction = d;
				details = details_;
				package_currently_delivering = nullptr;
				has_picked_up = false;
				distance_traveled = 0;
				helper_Create_Strategy(details);
			}

			/**
			 * @brief This function adds a package to a list of packages that a drone is currently bringing for delivery.
			 */
			void Pick_order();

			/**
			 * @brief This function removes the package from the package list of the drone indicating that the package was dropped.
			 */
			void Drop_order();
			/**
			 * @brief this function checks if the drone is within a certain range for performing and action.
			 * @param v Vector3D for the position to be checked if it is within the range 
			 */
			bool Within_range(Vector3D v);

			/**
			 * @brief This function returns the current position of the target in the currentRout vector. Used for either updating the drone's position or calculating routs.
			 */
			Vector3D GetTargetPosition();

			/**
			 * @brief This function has the simple goal of incrementing the vector of targets and returning the nnext target position, it would be similar to a GetTargetPosition+1.
			 */
			bool IncrTarget();

			/**
			 * @brief this function returns a pointer to the current package being carried by the drone
			 */
			Package* GetPackage();

			/**
			 * @brief this function assigns the package to be picked up by the drone to the drone that will picked it up.
			 * @param  pack a pointer to a package object to be assigned to the drone.
			 */
			void SetPackage(Package* pack);

			/**
			 * @brief this function return true or false if the drone battery is below 0 and if so it signals the observer that the entity is dead
			 * @return  the current state of the drone based on its battery level
			 */
			bool DroneAlive();

			/**
			 * @brief this function return true or false if the drone has delivered package
			 * @return  the current state of the drone based on if the package delivered
			 */
			bool Has_delivered_pack();

			/**
			 * @brief this function set the vector Drone_to_pack with the rout that the drone will follow from its current point to the package that it will eventually pick up.
			 * @param v  a vector of vector floats containing the rout generated by the graph
			 */
			void SetDroneToPack(std::vector<std::vector<float>> v);

			/**
			 * @brief similar to drone to pack, but in this case sets the pack_to_customer vector with the rout that the package will follow carried by the drone, from its current position to the customer that will receive it.
			 * @param v  a vector of vector float generated by the graph with the rout from the current position of the package to the customer.
			 */
			void SetPackToCustomer(std::vector<std::vector<float>> v);

			/**
			 * @brief a getter for the speed field, used on the calculation on the update function on delivery simulation
			 */
			float GetSpeed();

			/**
			 * @brief returns true if the drone is carrying a package and false otherwise.
			 */
			bool has_picked_up_getter();

			/**
			 * @brief this function determines if the current rout being followed by the drone is from its current position to the package, or from the package to the customer. In order words, if the drone is on its way to pick up the package or drop it off.
			 * @param rout a string to be compared if it is the rout from the drone to the package the string should be pack, if it is from the drone to the customer the string is customer 
			 */
			void SetCurrRout(std::string rout);

			/**
			 * @brief this function updates the package so it follows the drone in its movements
			 */
			void Update_Package();

			/**
			 * @brief this function returns the battery of the drone
			 * @return battery source of the drone
			 */
			Battery* GetBattery(){ return power_source; }

			/**
			 * @brief getter for the current index private variable
			 */
			int GetCurIndex() { return currentIndex; }

			/**
			 * @brief this function returns a pointer to the vector of vector floats that contain the current rout of the drone
			 */
			std::vector<std::vector<float>>& GetCurRout() { return currentRout ; }

			/**
			 * @brief getter for the distance traveled of a drone in float format
			 * @return returns the total distance travelled by the drone in float format
			 */
			float GetDistanceTraveled() { return distance_traveled; }

			/**
			 * @brief this function serves as a helper function to the schedule delivery in the delivery simulation file. By taking care of setting up the drone that will delivery the package or the customer that will receive it from a drone.
			 * @param package the package currently in the simulation
			 * @param dest the final destination of the drone and the package
			 */
			void Scheduled_drone(IEntity* package, IEntity* dest, const IGraph* graph_);

			/**
			 * @brief this function does all of the movements updates for the drone 
			 * through a series of calculation of Vector3D objects it moves the drone from point A to point B, 
			 * and selects when to drop and pick up the package calling the appropriate functions.
			 * @param dt the step change in the time of the simulation 
			 */
			void update_drone_movement(float dt);

			/**
			 * @brief The function updates the observer pattern of the drone mentioning that is idle 
			 */
			void OnIdle();

			/**
			 * @brief The function updates the package position currently held by the drone
			 * once the drone battery is completely dead 
			 */
			void Dead_Drop_order();

			/**
			 * @brief The function updates the observer pattern of the drone mentioning that it is moving 
			 */
			void OnMove();
			/**
			 * @brief Destructor for the Drone entity 
			 */
			~Drone () {
				delete strategy;
				delete power_source;
			}
			/**
			 * @brief The function helps to create the startegy for the drone to follow based on the path
			 * specified in the picojson object
			 * @param details The picojson object that consists of the details of the drone entity
			 */
			void helper_Create_Strategy(const picojson::object details);
		private:
			bool has_picked_up;
			std::vector<std::vector<float>> currentRout;
			int currentIndex = 0;
			Battery* power_source;
			float speed;
			float distance_traveled;
			std::vector<Package*> packages_delivered;
			std::vector<std::vector<float>>drone_to_pack;
			std::vector<std::vector<float>>pack_to_customer;
			Package* package_currently_delivering;
			IStrategy* strategy;
			bool has_delivered_pack;
			int dead_count = 0;
	}; //end of drone class

}
#endif