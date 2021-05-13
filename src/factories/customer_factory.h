/**
* @file customer_factory.h
**/
#ifndef CUSTOMER_FACTORY_H_
#define CUSTOMER_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <EntityProject/entity_factory.h>
#include "entities/customer.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief Customer factory creates new customers based on a picojson object
**/
class CustomerFactory : public IEntityFactory {
 public:

 /**
 * @brief constructor for customer factory
 **/
  CustomerFactory();

  /**
  * @brief destructor for customer factory
  **/
  ~CustomerFactory();

  /**
  * @brief Creates a new customer from the picojson object. If its not the correct type
  * returns null
  * @param val: The picojson object to create a customer from
  **/
  IEntity* CreateEntity(const picojson::object &val) override;
};

}

#endif  // SRC_CUSTOMER_FACTORY_H_