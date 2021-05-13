#include <stdexcept>
#include <fstream>
#include "factories/drone_factory.h"
#include "entities/drone.h"
#include "include/json_helper.h"

using std::string;

namespace csci3081 {

DroneFactory::DroneFactory() {}
DroneFactory::~DroneFactory() {}

IEntity* DroneFactory::CreateEntity(const picojson::object &val) {
  Drone* drone = NULL;
  picojson::object config(val);
  // Check type
  if (config["type"].get<std::string>() == "drone") {
    printf("In Drone Factory\n");
    auto init_pos = JsonHelper::GetStdFloatVector(config, "position");
    if(JsonHelper::ContainsKey(config, "battery_capacity"))
    {
      double init_batt = JsonHelper::GetDouble(config, "battery_capacity");
      drone = new Drone(init_pos, init_batt);
    }
    else
    {
      drone = new Drone(init_pos);
    }
    drone->SetDetails(val);
    try {
    drone->SetPath(JsonHelper::GetString(val, "path"));
    std::cout <<"GetString worked!\n";
    } catch(std::logic_error) {
      std::cout << "no path specified - choosing beeline route"<<std::endl;
      drone->SetPath("beeline");
    }
  }
  return drone;
}

}  // namespace csci3081
