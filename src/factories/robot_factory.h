/**
* @file robot_factory.h
**/
#ifndef ROBOT_FACTORY_H
#define ROBOT_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string>
#include <EntityProject/entity_factory.h>
#include "entities/robot.h"

namespace csci3081{

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief Customer factory creates new robots based on a picojson object
**/
class RobotFactory : public IEntityFactory{
    public: 

 /**
 * @brief constructor for robot factory
 **/
     RobotFactory();

  /**
  * @brief destructor for robot factory
  **/
     ~RobotFactory();

  /**
  * @brief Creates a new robot from the picojson object. If its not the correct type
  * returns null
  * @param val: The picojson object to create a robot from
  **/
     IEntity* CreateEntity(const picojson::object &val) override;

     private:
};

}

#endif      //  SRC_ROBOT_FACTORY_H