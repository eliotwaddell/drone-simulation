/**
* @file drone_factory.h
**/
#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

#include <string>
#include <EntityProject/entity_factory.h>
#include "entities/drone.h"

/*******************************************************************************
 * Includes
 ******************************************************************************/

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief Drone factory creates new drones based on a picojson object
**/
class DroneFactory : public IEntityFactory {
 public:

/**
 * @brief constructor for drone factory
 **/
  DroneFactory();

  /**
  * @brief destructor for drone factory
  **/
  ~DroneFactory();

  /**
  * @brief Creates a new drone from the picojson object. If its not the correct type
  * returns null
  * @param val: The picojson object to create a drone from
  **/
  IEntity* CreateEntity(const picojson::object &val) override;

 private:
};

}

#endif  // SRC_DRONE_FACTORY_H_