#include <stdexcept>
#include <fstream>
#include "factories/robot_factory.h"
#include "entities/robot.h"
#include "include/json_helper.h"

using std::string;

namespace csci3081{

RobotFactory::RobotFactory() {}

RobotFactory::~RobotFactory() {}

IEntity* RobotFactory::CreateEntity(const picojson::object &val){
    std::cout <<"In robot factory\n";
    Robot* robot = NULL;
    picojson::object config(val);
    //  Check type
    if (config["type"].get<std::string>() == "robot"){
        printf("In Robot Factory\n");
        auto init_pos = JsonHelper::GetStdFloatVector(config, "position");
        if(JsonHelper::ContainsKey(config, "battery_capacity"))
        {
          double init_batt = JsonHelper::GetDouble(config, "battery_capacity");
          robot = new Robot(init_pos, init_batt);
        }
        else
        {
          robot = new Robot(init_pos);
        }
        robot->SetDetails(val);
    }
    return robot;
}

}
