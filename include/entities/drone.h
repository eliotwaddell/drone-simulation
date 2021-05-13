/**
* @file drone.h
**/
#ifndef DRONE_H_
#define DRONE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <cmath>
#include <queue>
#include <iostream>
#include <vector>
#include "json_helper.h"
#include "entities/delivery_entity.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief The Drone class is one of the delivery entities that delivers packages to customers
**/
class Drone : public DeliveryEntity {
  private:
    std::string path_;
    PathContext *path_context;
    const IGraph *graph_;
 public:

 /**
 * @brief Destructor for the Drone class
 **/
  virtual ~Drone() {
    delete battery_;
  }

  /**
  * @brief Sets the graph object for the drone in order for it to implement the smart route
  * @param graph: The IGraph* that graph_ will be set to
  **/
  void SetGraph(const IGraph* graph){
    graph_ = graph;
  }

  /**
  * @brief Constructor for the Drone class that takes in a initial position
  * @param position: The initial position of the drone, represented by a vector of floats
  **/
  Drone(std::vector<float> position) {
    SetPosition(position);
    battery_ = new Battery;
      SetType(DRONE);
  }

  /**
  * @brief Constructor for the Drone class that takes in a position and a max battery life
  * @param position: The initial position of the drone, represented by a vector of floats
  * @param max: The max charge of the battery of the drone
  **/
  Drone(std::vector<float> position, float max) {
    SetPosition(position);
    battery_ = new Battery(max);
    SetType(DRONE); }

  /**
  * @brief Updates the drone in the simulation by dt time
  * @param dt: The amount of time to update the drone by
  **/
  void Update(float dt);

  /**
  * @brief Picks up the package once the drone is within the radius of the package
  * and sets the route from the position of the package to the customer assigned to it
  **/
  void PickUpPackage(){
      path_context = new PathContext(path_);
      path_context->SetGraph(graph_);
      auto route = path_context->GetRoute(scheduled_package->GetPosition(), scheduled_package->GetCustomer()->GetPosition());
      if (route.size() == 0) printf("There is no path from package to customer!\n");
      routeTarget_ = 0;
      route_ = Vector3D::BuildRoute(route);
      has_package = true;
      scheduled_package->NotifyObservers("notify", "en route");
  }

  /**
  * @brief Returns the type of path the drone should take as specified by the picojson object
  **/
  std::string GetPath(){ return path_; }

  /**
  * @brief Sets the type of path the drone should take from a point to a point
  * @param path: The type of path the drone should take. Represented by a string
  **/
  void SetPath(std::string path){ path_ = path; }


};
}  // namespace csci3081

#endif  // SRC_DRONE_H_
