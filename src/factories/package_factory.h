/**
* @file package_factory.h
**/
#ifndef PACKAGE_FACTORY_H_
#define PACKAGE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <EntityProject/entity_factory.h>
#include "entities/package.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief package factory creates new packages based on a picojson object
**/
class PackageFactory : public IEntityFactory {
 public:

 /**
 * @brief constructor for package factory
 **/
  PackageFactory();

  /**
  * @brief destructor for package factory
  **/
  ~PackageFactory();

  /**
  * @brief Creates a new package from the picojson object. If its not the correct type
  * returns null
  * @param val: The picojson object to create a package from
  **/
  IEntity* CreateEntity(const picojson::object &val) override;
};
}  // namespace csci3081

#endif  // SRC_PACKAGE_FACTORY_H_