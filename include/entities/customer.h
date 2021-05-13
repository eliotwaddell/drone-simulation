/**
* @file customer.h
**/
#ifndef CUSTOMER_H_
#define CUSTOMER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "entity_base.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief The customer class represents the final location of a package in order for it to be considered delivered
* is one of the three entity types that are shown in the simulation
**/
class Customer : public EntityBase {
 public:
  /**
  * @brief Customer constructor that takes in a position of the customer
  * @param position: The position of the customer in the simulation. Represented as a vector of floats
  **/
  Customer(std::vector<float> position) { SetPosition(position); SetType(CUSTOMER); }
  
  /**
  * @brief Destructor for customer class
  **/
  virtual ~Customer() {}
};

}  // namespace csci3081

#endif  // SRC_CUSTOMER_H_