/**
 *@file ISubject.h
 */
#ifndef ISUBJECT_H_
#define ISUBJECT_H_
/**
 * include
 */
#include <EntityProject/facade/delivery_system.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "json_helper.h"
#include <vector>

namespace csci3081 {

	class ISubject {
		/**
		 * @brief the subject class will be used as part of the observer pattern to notify the appropriate entities to changes made in the simulation.
		 */
		private:
			// a list of observers that are watching the current subject.
			std::vector<IEntityObserver*> observers_;

		public:
			/**
			 * @brief This methods adds observers to the observers vector.
			 * @param[In] observer_to_be_added: an observer to be added to the observers vector.
			 */
			void AddObserver(IEntityObserver* observer_to_be_added);
			/**
			 * @brief this method removes observers from the observers vector.
			 * @param[In] the observer entity to be removed from the observers vector.
			 */
			void RemoveObserver(IEntityObserver* observer_to_be_removed);
			/**
			 * @brief this method will loop through all the observers and call the IEntityObserver OnEvent method on all of them.
			 * @param[In] object: picojson object to be used to determine what kind of notifications to send to the entities.
			 * @param[In] entity: an IEntity object that points to the current entity that will notify the observers.
			 */
			void OnEvent(const picojson::value& object, const IEntity& entity_);

	}; //close class.

}//close namespace 
// namespace csci3081
#endif // ISUBJECT_H_