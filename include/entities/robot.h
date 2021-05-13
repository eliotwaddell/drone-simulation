/**
* @file robot.h
**/
#ifndef ROBOT_H_
#define ROBOT_H_

 /*******************************************************************************
 * Includes
 ******************************************************************************/

#include <cmath>
#include <queue>
#include <iostream>
#include <vector>

#include "entities/delivery_entity.h"

namespace csci3081{

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/*
* @brief The Robot class is one of the delivery entities that delivers packages to customers
**/
class Robot : public DeliveryEntity{

    public:

    /**
    * @brief Destructor for Robot class
    **/
    virtual ~Robot() {
          delete battery_;
      }

    /**
    * @brief Constructor for Robot that takes in a position
    * @param position: the initial position of the robot represented as a vector of floats
    **/
      Robot(std::vector<float> position) {
          SetPosition(position);
          battery_ = new Battery;
          SetType(ROBOT);
      }


    /**
    * @brief Picks up the package once the robot is within the radius of the package
    * and sets the route from the position of the package to the customer assigned to it
    **/
    void PickUpPackage(){
        auto route = graph_->GetPath(scheduled_package->GetPosition(), scheduled_package->GetCustomer()->GetPosition());
        if (route.size() == 0) printf("There is no path from package to customer!\n");
        routeTarget_ = 0;
        route_ = Vector3D::BuildRoute(route);
        has_package = true;
        scheduled_package->NotifyObservers("notify", "en route");
  }

    /**
    * @brief Constructor for Robot that takes in an initial position and max battery percentage
    * @param position: The initial position of the robot, represented as a vector of floats
    * @param max: The max battery percentage that the robot has
    **/
      Robot(std::vector<float> position, float max) {
        SetPosition(position);
        battery_ = new Battery(max);
        SetType(ROBOT); }

    /**
    * @brief Updates the robot in the simulation by a given period of time
    * @param dt: the amount of time to update the robot by
    **/
     void Update(float dt);


};


}   //  namespace csci3081

#endif      //SRC_ROBOT_H_
