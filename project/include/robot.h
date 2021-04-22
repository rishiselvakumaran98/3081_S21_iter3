/**
 * @file Robot.h
 */
#ifndef ROBOT_H_
#define ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>
#include <string>
#include "Package.h"
#include "Vector2D.h"
#include "Battery.h"

namespace csci3081 {
   /*******************************************************************************
    * Class Definitions
    ******************************************************************************/
   /**
    * @brief These are the methods that will be used for the Robot class.
    *
    * This class will have functions that control a Robot, pick up and drop off packages. Also, private fields for keep track of the speed and other variables relevant to a Robot.
    */
	class Robot : public csci3081::EntityBase {

	public:
		/**
		 * @brief basic constructor for a Robot object. Taking a picojson object that received from entity base.
		 * @param details_ the picojson from the facade to be used as a setup for the entity
		*/
		Robot(const picojson::object& details_):csci3081::EntityBase(details_) {
			details = details_;
			package_currently_delivering = nullptr;
			speed = JsonHelper::GetDouble(details_, "speed");
			has_picked_up = false;
			distance_traveled = 0;
			float battery_capacity;
			if(JsonHelper::ContainsKey(details_, "battery_capacity")){
				battery_capacity = JsonHelper::GetDouble(details_, "battery_capacity");
			}else
				battery_capacity = 10000;
			power_source = new Battery(battery_capacity, "xc");
			has_delivered_pack = false;
		}
		

		/**
		 * @brief more complex constructor for Robots
		 * @param s s-value for speed of the Robot
		 * @param b pointer to a Battery to be implemented on the Robot
		 * @param details_ the picojson from the facade 
		 */
		Robot(float s, Battery* b, const picojson::object& details_):EntityBase(details_) {
			speed = s;
			power_source = b;
			details = details_;
			package_currently_delivering = nullptr;
			has_picked_up = false;
			distance_traveled = 0;
		}//close constructor 

		/**
		 * @brief another constructor for Robots
		 * @param p the vector float to be used as the position of the Robot 
		 * @param d the direction float vector of the Robot
		 * @param details the picojson object form the facade 
		 */
		Robot(std::vector<float> p, std::vector<float> d, const picojson::object& details_):EntityBase(details_) {
			position = p;
			direction = d;
			details = details_;
			package_currently_delivering = nullptr;
			has_picked_up = false;
			distance_traveled = 0;
		}//close constructor

		/**
		 * @brief This function adds a package to a list of packages that a Robot is currently bringing for delivery.
		 */
		void Pick_order();

		/**
		 * @brief This function removes the package from the package list of the Robot indicating that the package was dropped.
		 */
		void Drop_order();

		/**
		 * @brief this function checks if the Robot is within a certain range for performing and action.
		 * @param v Vector3D for the position to be checked if it is within the range 
		 */
		bool Within_range(Vector3D v);

		/**
		 * @brief This function returns the current position of the target in the currentRout vector. Used for either updating the Robot's position or calculating routs.
		 */
		Vector3D GetTargetPosition();


		/**
		 * @brief This function has the simple goal of incrementing the vector of targets and returning the nnext target position, it would be similar to a GetTargetPosition+1.
		 */
		bool IncrTarget();

		/**
		 * @brief this function returns a pointer to the current package being carried by the Robot
		 */
		Package* GetPackage();

		/**
		 * @brief this function assigns the package to be picked up by the Robot to the Robot that will picked it up.
		 * @param  pack a pointer to a package object to be assigned to the Robot.
		 */
		void SetPackage(Package* pack);
		/**
		 * @brief this function return true or false if the drone battery is above 0
		 * @return  the current state of the drone based on its battery level
		 */
		bool RobotAlive();

		/**
		 * @brief this function return true or false if the robot has delivered package
		 * @return  the current state of the robot based on if the package delivered
		 */
		bool Has_delivered_pack();
		/**
		 * @brief this function set the vector Robot_to_pack with the rout that the Robot will follow from its current point to the package that it will eventually pick up.
		 * @param v  a vector of vector floats containing the rout generated by the graph
		 */
		void SetRobotToPack(std::vector<std::vector<float>> v);

		/**
		 * @brief similar to Robot to pack, but in this case sets the pack_to_customer vector with the rout that the package will follow carried by the Robot, from its current position to the customer that will receive it.
		 * @param v  a vector of vector float generated by the graph with the rout from the current position of the package to the customer.
		 */
		void SetPackToCustomer(std::vector<std::vector<float>> v);

		/**
		 * @brief a getter for the speed field, used on the calculation on the update function on delivery simulation
		 */
		float GetSpeed();

		/**
		 * @brief returns true if the Robot is carrying a package and false otherwise.
		 */
		bool has_picked_up_getter();

		/**
		 * @brief this function determines if the current rout being followed by the Robot is from its current position to the package, or from the package to the customer. In order words, if the Robot is on its way to pick up the package or drop it off.
		 * @param rout a string to be compared if it is the rout from the Robot to the package the string should be pack, if it is from the Robot to the customer the string is customer 
		 */
		void SetCurrRout(std::string rout);

		/**
		 * @brief this function updates the package so it follows the Robot in its movements
		 */
		void Update_Package();

		/**
		 * @brief getter for the current index private variable
		 */
		int GetCurIndex() { return currentIndex; }

		/**
		 * @brief this function returns a pointer to the vector of vector floats that contain the current rout of the Robot
		 */
		std::vector<std::vector<float>>& GetCurRout() { return currentRout ; }

		/**
		 * @brief getter for the distance traveled of a Robot in float format
		 */
		float GetDistanceTraveled() { return distance_traveled; }

		/**
		 * @brief this function serves as a helper function to the schedule delivery in the delivery simulation file. By taking care of setting up the Robot that will delivery the package or the customer that will receive it from a Robot.
		 * @param package the package currently in the simulation
		 * @param dest the final destination of the Robot and the package
		 */
		void Scheduled_Robot(IEntity* package, IEntity* dest, const IGraph* graph_);

		/**
		 * @brief this function does all of the movements updates for the Robot 
		 * through a series of calculation of Vector3D objects it moves the Robot 
		 * from point A to point B, and selects when to drop and pick up the package 
		 * calling the appropriate functions.
		 * @param dt The change delta in the time for the updating the drone movements
		 */
		void update_Robot_movement(float dt);
		/**
		 * @brief This method helps in dropping the package to the ground position (y=0) 
		 * if the robot battery dies midway through when the robot is delvering package
		 */
		void Dead_Drop_order();
		/**
		 * @brief This would be observer method that updates the simulation observer that the robot
		 * has stopped moving
		 */
		void OnIdle();
		/**
		 * @brief This would be observer method that updates the simulation observer that the robot
		 * has is moving on its current path to the Package or Customer
		 */
		void OnMove();


	private:
		bool has_picked_up;
		std::vector<std::vector<float>> currentRout;
		int currentIndex = 0;
		Battery* power_source;
		float speed;
		float distance_traveled;
		std::vector<Package*> packages_delivered;
		std::vector<std::vector<float>>Robot_to_pack;
		std::vector<std::vector<float>>pack_to_customer;
		Package* package_currently_delivering;
		bool has_delivered_pack;
	}; //end of Robot class

}
#endif