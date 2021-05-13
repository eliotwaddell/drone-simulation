#include <vector>
#include "entities/robot.h"
#include "json_helper.h"
#include "entities/delivery_decorator.h"
#include "entities/blue_decorator.h"
#include "entities/green_decorator.h"
#include "entities/white_decorator.h"

namespace csci3081 {

  void Robot::Update(float dt) {
    DeliveryEntity* decorator = new DeliveryDecorator(this);
    if (routeTarget_ >= route_.size()) {
      routeTarget_ = 0;
      route_.clear();
      is_moving = false;
    }
    if (!scheduled_package->Delivered() && !is_moving) { is_moving = true;
        this->NotifyObservers("notify", "moving", route_);
     }

     if(is_moving)
     {
         if(has_package)
         {
           decorator = new BlueDecorator(decorator);
           decorator->ColorEntity();
           this->NotifyObservers("notify", "updateDetails", decorator->GetDetails());
         }
         else
         {
           decorator = new GreenDecorator(decorator);
           decorator->ColorEntity();
           this->NotifyObservers("notify", "updateDetails", decorator->GetDetails());
         }
     }
     else
     {
       decorator = new WhiteDecorator(decorator);
       decorator->ColorEntity();
       this->NotifyObservers("notify", "updateDetails", decorator->GetDetails());
     }

    Vector3D target_position = route_[routeTarget_];
    Vector3D position = Vector3D(this->GetPosition());
    if ((position -target_position).Magnitude() <= this->GetRadius()) {
      if (routeTarget_ == route_.size() - 1) {
        printf("Reached last node\n");
        if (!has_package && this->ScheduledPackage()) {
          this->PickUpPackage();

          this->NotifyObservers("notify", "moving", route_);
        } else if (has_package) {
          this->DropOffPackage();
          routeTarget_ = 0;
          route_.clear();

          this->NotifyObservers("notify", "idle");
        } else {
          printf("Drone likely did not receive proper route");
        }
      }
      if (routeTarget_ < route_.size()) {
        printf("incrementing routeTarget_: %i of %i\n", routeTarget_, (int) route_.size() - 1);
        routeTarget_ += 1;
      }
    }
    if (is_moving) {
      Vector3D direction = (target_position - position).Normalize();
      Vector3D next = position += (direction.Normalize() *= dt);
      this->SetPosition(next.ToVector());
      this->UpdateScheduledPackage();
      battery_->DepleteBattery(dt); // Deplete Battery
      if(battery_->IsDead())
      {
        this->BatteryDeath();
      }
    }
  }

}
