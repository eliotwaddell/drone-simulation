/**
* @file battery.h
**/
#ifndef BATTERY_H_
#define BATTERY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief The battery class is used to keep track of the battery power of the drone
**/
class Battery {
 public:

  /**
  *@brief The destructor for Battery
  **/
  ~Battery() {}

  /**
  * @brief The default constructor for a Battery
  **/
  Battery() {}

  /**
  * @brief A constructor to make a battery with a specified max charge 
  * @param max_charge: The float value to set the battery's max charge to
  **/
  Battery(float max_charge);

  /**
  * @brief returns true if the battery is out of battery, false if not
  **/
  bool IsDead() { return dead_battery_; }

  /**
  * @brief returns the charge left in the battery
  **/
  float ChargeLeft() { return remaining_battery_; }

  /**
  * @brief Depletes the battery charge by a specified amount
  * @param dt: The amout of percentage to decrease the battery by
  **/
  void DepleteBattery(float dt);

 private:
  bool dead_battery_ = false;
  float max_charge_ = 10000;
  float remaining_battery_ = 10000;
};

}  // namespace csci3081

#endif  // SRC_BATTERY_H_