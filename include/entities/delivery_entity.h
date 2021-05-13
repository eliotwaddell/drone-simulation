/**
* @file delivery_entity.h
**/
#ifndef DELIVERY_ENTITY_H_
#define DELIVERY_ENTITY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "entity_base.h"
#include "entities/package.h"
#include "entities/battery.h"
 #include "json_helper.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

namespace csci3081{

/**
* @brief The general delivery entity class for drone and robot to inherit off of to
* shared common functions and attributes
**/
class DeliveryEntity : public EntityBase{

 public:

  /**
  * @brief Destructor for DeliveryEntity
  **/
   ~DeliveryEntity() {
    delete battery_;
  }

  /**
  * @brief returns true if the entity is scheduled, false otherwise
  **/
  bool IsScheduled() { return scheduled;}

  /**
  * @brief Updates the entity in the simulation by a set amount of time
  * @brief dt: The amount of time to update the entity in the simulation
  **/
  void Update(float dt);

  /**
  * @brief Assigns a package for the entity to pick up
  * @param p: The package to be picked up by the entity
  **/
  void AssignPackage(Package* p) { scheduled_package = p; scheduled = true; }
  /**
   * @brief Function for when a Delivery Entity runs out of battery
   *
   * In the case that a Delivery Entity runs out of battery, they unschedule their
   * package, and change their scheduled status and has_package status to false
   */

  void AbandonPackage() { scheduled_package = nullptr; scheduled = false; has_package = false; }

  /**
  * @brief Returns true if a package is scheduled, false if a package is not
  **/
  bool ScheduledPackage() { return (scheduled_package != nullptr); }

  /**
  * @brief returns true if the entity has a package, false if not
  * @param p: the package to check if the entity has
  **/
  bool HasPackage(Package* p) { return has_package; }

  /**
  * @brief Sets the IGraph* of the entity
  * @param graph: The IGraph* to set within the entity
  **/
  void SetGraph(const IGraph* graph) { graph_ = graph; }

  /**
  * @brief Returns the amount of battery life the entity has left
  **/
  float GetRemainingBattery() const { return battery_->ChargeLeft(); };

  /**
  * Returns the route of the entity
  **/
  const std::vector<Vector3D>& GetRoute() const { return route_; }

  /**
  * @brief returns true if the entity is moving, false otherwise;
  **/
  bool IsDynamic() const override { return true; }

  /**
  * @brief returns the package that the entity is scheduled to get
  **/
  Package* GetPackage() { return scheduled_package; }

  /**
  * @brief sets the route for the entity to take
  * @param route: The vector of Vector3D's for the entity to take to get to a destination
  **/
  void SetRoute(std::vector<Vector3D> route) { route_ = route; routeTarget_ = 0; }

  virtual void ColorEntity() {this->NotifyObservers("notify", "updateDetails", this->details_);}

 protected:
  std::vector<Vector3D> route_;
  const IGraph* graph_;
  int routeTarget_ = -1;
  bool has_package = false;
  Battery* battery_ = nullptr;
  bool is_moving = false;
  Package* scheduled_package = nullptr;
  bool scheduled = false;

  /**
  * @brief drops the package off at a customer and stops the entity's movement until another is scheduled
  **/
  void DropOffPackage(){
    has_package = false;
    is_moving = false;
    scheduled_package->Deliver();
    this->SetPosition(scheduled_package->GetCustomer()->GetPosition());
    this->SetDirection({0, 1, 0});

    scheduled_package->NotifyObservers("notify", "delivered");
    scheduled = false;
  }

  /**
  * @brief Updates the package's movement to the entity's as it moves through the simulation
  **/
  void UpdateScheduledPackage() { if (has_package) scheduled_package->SetPosition(position_);  }

  /**
   * @brief Drone constructor with specified position
   *
   * Takes two parameters, one representing the Drone's position, which is
   * used to initialize it, and one representing and setting the Drone's max
   * battery capacity.
   */

  void BatteryDeath()
  {
    is_moving = false;
    route_.clear();
    routeTarget_ = 0;
    scheduled_package->Reschedule();

    this->NotifyObservers("notify", "idle");
  }


};




}

#endif  //    DELIVERY_ENTITIY_H_
