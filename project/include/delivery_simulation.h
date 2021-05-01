/**
 * @file delivery_simulation.h
 */
#ifndef DELIVERY_SIMULATION_H_
#define DELIVERY_SIMULATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include <string>
#include "drone.h"
#include "Package.h"
#include "Vector3D.h"
#include "Customer.h"
#include "json_helper.h"
#include "entity_base.h"
// #include "Vector2D.h"
#include "CompositeFactory.h"
#include "DroneFactory.h"
#include "PackageFactory.h"
#include "CustomerFactory.h"
#include "RobotFactory.h"
#include "IEntityFactory.h"
#include "ISubject.h"
#include "SingletonCSV.h"
#include "ScheduleDelivery.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the facade for the delivery system
 *
 * This class will delegate operations for the whole drone delivery system.
 * See the documentation for IDeliverySystem for more information.
 */

// DO NOT MODIFY (unless you really know what you are doing)
class DeliverySimulation : public IDeliverySystem {
 public:
  /**
   * @brief Constructor: this can do any setup your system necessitates.
   */
  DeliverySimulation();

  /// Desconstructor: This should free any memory that your program uses.
  ~DeliverySimulation();

  /**
  Given the picojson::object val, this should create an entity.
  Based on the type of entity, there may be different fields.
  You can see the vals that will be passed in the project/web/scenes
    directory. Some of the fields are for our backend system and you don't
    need to worry about them. (for instance, mesh, rotation, offset, etc.)

  Some fields in val that you will need to create the entity correctly:

    type: string (could be "drone/customer/package")

    name: string

    position: array (contains [x_position, y_position, z_position])

    direction: array (contains [x, y, z])

    speed: float

    battery_capacity: float

  Don't add the entity to the simulation until it is passed in via AddEntity
  */
  IEntity* CreateEntity(const picojson::object& val);

  /**
   *  This function should add a factory to the composite factory pattern
   */
  void AddFactory(IEntityFactory* factory);

  /**
   *  This function should add an entity to the simulation
   */
  void AddEntity(IEntity* entity);

  /**
  This function should simply store a reference to the IGraph* somewhere.
  The IGraph contains useful functions such as the GetPath function which can 
  be used to get a path from one position to another.
  */
  void SetGraph(const IGraph* graph);

  /**
  This function tells the simulation that the IEntity* package should be delivered
  to the IEntity* dest (which is likely a customer). How the delivery takes place
  is entirely dependent on how you design your code, but it should involve a drone
  navigating to the package, picking it up, and then moving to the customer and 
  dropping the package.
  */
  void ScheduleDelivery(IEntity* package, IEntity* dest);
  /**
   * @brief This function actually schedules the Drone and Robot entities with packages 
   * and the respective customer destination that the drone should deliver to. The function
   * uses a queue data structure to assign the avaible package and customer to the empty
   * drones and customers. 
   * 
   */
  void ActualScheduleDelivery();
  /**
   * @brief This function reschedules the packages that is abandoned by the drone due to its low 
   * battery status. The function takes in a Package *pack from the drone and it assigns it uses the 
   * ActualScheduleDelivery() to schedule the package to the drone or robot that is alive and running
   * 
   */
  void RescheduleDelivery(Package *pack);
  /**
   * @brief This function adds the respective observer to the ISubject entity in the simulation
   */
  void AddObserver(IEntityObserver* observer);
  /**
   * @brief This function removes the respective observer to the ISubject entity in the simulation
   */
  void RemoveObserver(IEntityObserver* observer);

  /**
  GetEntities should return all entities that have been ADDED to the system
  */
  const std::vector<IEntity*>& GetEntities() const;

  /**
  This function is used to advance time in the simulation. float dt refers to the 
  amount of time the update call should advance the simulation by. For instance if a drone
  moves 1 unit of distance per unit of time, and Update is called with dt=.05, then the
  drone should move 1 * .05 = .05 units of distance.

  Some things that should happen in the Update function: move drones, check if
  packages have been delivered to customers, etc.
  */

  void Update(float dt);

  /**
   * @brief You do not need to worry about this function
   * 
   * This function takes care of turning json into function calls of your system.
   * YOU DO NOT NEED TO IMPLEMENT THIS
   *it is already implemented in the delivery_simulation.cc we have provided.
   */
  void RunScript(const picojson::array& script, IEntitySystem* system) const;
  /**
   * @brief This function increments the ID for the entities for the 
   */
  int NewId() {
	  Id++;
	  return Id;
  }
 private:
  // You don't strictly need to use the following variable, but it is probably
  // the most straightforward way of storing the entities in the system.
  // Feel free to use it as is or change it.
  std::vector<IEntity*> entities_;
  std::vector<IEntity*> packages_array;
  std::vector<IEntity*> customer_array;
  const IGraph* graph_;
  CompositeFactory comp_fact;
	int Id = -1;
	ISubject isub;
  int schedule_count = 0;
  int drone_rescheduleCount = 0;
  int robot_rescheduleCount = 0;
  std::vector<std::string> files;
  float dt_temp = 0;
  SingletonCSV* sing;
  ScheduleDelivery_Helper *deliverer;
};

}  // namespace csci3081


#endif  // DELIVERY_SIMULATION_H_
