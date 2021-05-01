/**
 *@file ScheduleDelivery.h
 */
#ifndef SCHEDULE_DELIVERY_H
#define SCHEDULE_DELIVERY_H
/**
 * include
 */
#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include <string>
#include "robot.h"
#include "drone.h"
#include "Package.h"
#include "Vector3D.h"
#include "Customer.h"
#include "json_helper.h"
#include "entity_base.h"

namespace csci3081 {
    /*******************************************************************************
	 * Class Definitions
	 ******************************************************************************/
	/**
	 * @brief ScheduleDelivery_Helper. This class is responsible for helping the entities created in the delivery
     * simulation to schedule their respective packages.
	*/
    class ScheduleDelivery_Helper{
        public:
            /**
			 * @brief This function helps to reschedule the delivery for the packages to their respective entities once the entity carrying it dies due to low battery
			 * @param[in] pack the package that we are interested in reassigning.
             * @param[in] packages_array a vector of package entities that gets reshuffled and assigned within the entities
             * @param[in] customer_array a vector of customers that are recipients of the packages
			 */
            void RescheduleDelivery_helper(Package *pack, std::vector<IEntity*>& packages_array, std::vector<IEntity*>& customer_array);
            /**
			 * @brief This function helps to Schedule the delivery for the packages with their respective entities based on a first come first serve basis
			 * @param[in] entities_ vector of entities that are checked and assigned their respective roles 
             * @param[in] packages_array a vector of package entities that gets assigned within the entities
             * @param[in] customer_array a vector of customers that are recipients of the packages
             * @param[in] graph_ The variable responsible for the generating the smart algorithm from the facade to give array of directions to the drone
			 */
            void Schedule_Delivery_Entities(std::vector<IEntity*>& entities_, 
                    std::vector<IEntity*>& packages_array, std::vector<IEntity*>& customer_array, const IGraph* graph_);
    };
}

#endif