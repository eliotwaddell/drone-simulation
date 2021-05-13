/**
* @file package.h
**/
#ifndef PACKAGE_H_
#define PACKAGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string>
#include <vector>
#include "entity_base.h"
#include "entities/customer.h"

namespace csci3081 {

/*******************************************************************************
 * Includes
 ******************************************************************************/

/**
* @brief The package class represents the package in the simulation that will be delivered
* to a customer via drone or robot
**/

class Package : public EntityBase {
 public:

  /**
  * @brief Constructor for a package that takes in a position
  * @param position: The position of the package in the simulation, represented by a vector or floats
  **/
  Package(std::vector<float> position) { SetPosition(position); SetType(PACKAGE); }

  /**
  * @brief Destructor for the Package class
  **/
  virtual ~Package() { delete customer_; }

  /**
  * @brief Assigns a customer object that the package should be delivered to
  * @param customer: The customer object that the package should be delivered to
  **/
  void AssignCustomer(Customer* customer) { customer_ = customer; }

  /**
  * @brief returns the customer that the drone is assigned to
  **/
  Customer* GetCustomer() { return customer_; }

  /**
  * @brief Returns true if the package should be moving, false if not
  **/
  bool IsDynamic() const override { return true; }

  /**
  * @brief returns the weight of the package
  **/
  float GetWeight() const { return weight_; };

  /**
  * @brief sets the weight of the package
  * @param weight: The value that the package's weight should be assigned
  **/
  void SetWeight(float weight) {weight_ = weight; }

  /**
  * @brief Prints out that the package is delivered and sends the package off the simulation
  **/
  void Deliver();

  /**
  * @brief returns true if the package is delivered, false if not
  **/
  bool Delivered() { return delivered_; }

  /**
  * @brief Sets the package's height to 0 (as if a drone or robot dropped it)
  **/
  void Reschedule();

 private:
  Customer* customer_;
  float weight_ = 0;
  bool delivered_ = false;
};

}  // namespace csci3081

#endif  // SRC_PACKAGE_H_
