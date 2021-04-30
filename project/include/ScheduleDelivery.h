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
    class ScheduleDelivery_Helper{
        public:
            void RescheduleDelivery_helper(Package *pack, std::vector<IEntity*>& packages_array, std::vector<IEntity*>& customer_array);
            void Schedule_Delivery_Entities(std::vector<IEntity*>& entities_, 
            std::vector<IEntity*>& packages_array, std::vector<IEntity*>& customer_array, const IGraph* graph_);
    };
}

#endif