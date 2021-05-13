/**
* @file composite_factory.h
**/
#ifndef COMPOSITE_FACTORY_H_
#define COMPOSITE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <EntityProject/entity_factory.h>
#include "factories/drone_factory.h"
#include "factories/robot_factory.h"
#include "entity_base.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief The composite factory uses the composite factory method to create drones, robots
* packages, and customers for the simulation
**/
class CompositeFactory : public IEntityFactory {
 public:

  /**
  * @brief The constructor for composite factory
  **/
  CompositeFactory();

  /**
  * @brief The destructor for composite factory
  **/
  ~CompositeFactory();

  /**
  * @brief Creates a new entity using the given picojson object and the entity factories
  * @param val: The picojson object to create the entity from
  **/
  IEntity* CreateEntity(const picojson::object &val) override;

  /**
  * @brief Adds a new factory to the vector of factories in composite factory
  * @param factory: The new factory to add to the vector
  **/
  void AddFactory(IEntityFactory* factory);

 private:
  std::vector<IEntityFactory*> factories_;
};

}

#endif  // SRC_COMPOSITE_FACTORY_H_