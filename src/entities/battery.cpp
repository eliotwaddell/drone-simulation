#include "entities/battery.h"

namespace csci3081 {

Battery::Battery(float max_charge) {
  remaining_battery_ = max_charge;
  max_charge_ = max_charge;
}

void Battery::DepleteBattery(float dt) {
  remaining_battery_ -= dt;
  if (remaining_battery_ <= 0) {
    remaining_battery_ = 0;
    dead_battery_ = true;
  }
}

}