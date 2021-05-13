/**
 * @file delivery_simulation.h
 */
#ifndef DELIVERY_SIMULATION_H_
#define DELIVERY_SIMULATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include "entities/drone.h"
#include "entities/robot.h"
#include "factories/composite_factory.h"
#include <vector>
#include <string>

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

  /**
  * @brief Destructor: This destroys any newly created objects to prevent memory leaks
  **/
  ~DeliverySimulation();

  /**
  * @brief Creates a new Entity based on the picojson object passed in
  * @param val: is a picojson object that is used to establish the entity's information
  */
  IEntity* CreateEntity(const picojson::object& val);

  /**
  * @brief Removes an entity from the simulation
  * @param entity: the specific entity for the simulation to remove
  **/
  void RemoveEntity(IEntity* entity);

  /**
   * @brief Adds a new factory to the simulation to create new entities
   * @param factory: A factory object that creates new entities in the simulation
   */
  void AddFactory(IEntityFactory* factory);

  /**
   * @brief Adds a new entity to the simulation
   * @param entity: A IEntity object to add to the simulation
   */
  void AddEntity(IEntity* entity);

  /**
  * @brief Sets the graph object of the simulation
  * @param graph: A IGraph pointer to set the graph object of the simulation to
  */
  void SetGraph(const IGraph* graph);

  /**
  * @brief Schedules a delivery for a drone or robot to take the package to the destination(customer)
  * @param package: A IEntity package pointer for a drone or robot to pickup
  * @param dest: A IEntity customer pointer for a drone or robot to deliver a package to
  */
  void ScheduleDelivery(IEntity* package, IEntity* dest);

  /**
  * @brief Adds a new observer to the simulation
  * @param observer: the new observer to add to the simulation
  */
  void AddObserver(IEntityObserver* observer);

  /**
  * @brief Removes an observer from the simulation
  * @param observer: the observer to remove from the simulation
  */
  void RemoveObserver(IEntityObserver* observer);

  /**
  * @brief returns the vector of entities within the simulation
  */
  const std::vector<IEntity*>& GetEntities() const;

  /**
  * @brief Updates the entities in the simulation by dt time
  * @param dt: The amount of time to update the entities by
  */
  void Update(float dt);

  /**
  * @brief Returns a unique Id for each entity in the simulation
  **/
  int Uid();

  /**
   * @brief You do not need to worry about this function
   *
   * This function takes care of turning json into function calls of your system.
   * YOU DO NOT NEED TO IMPLEMENT THIS
   *it is already implemented in the delivery_simulation.cc we have provided.
   */
  void RunScript(const picojson::array& script, IEntitySystem* system) const;



 private:
  std::vector<IEntity*> entities_;
  std::vector<IEntityObserver*> observers_;
  std::vector<Drone*> scheduled_drone;
  std::vector<Robot*> scheduled_robot;
  std::vector<Customer*> unscheduled_customer;
  std::vector<Package*> unscheduled_package;
  CompositeFactory* entity_factory_;
  int id_ = -1;
  const IGraph* graph_;
  PathContext *path_;

};

}  // namespace csci3081


#endif  // DELIVERY_SIMULATION_H_
