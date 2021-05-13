/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "gtest/gtest.h"
#include "entities/robot.h"
#include "json_helper.h"

namespace csci3081{


/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class RobotTest : public ::testing::Test{
    protected:
    virtual void SetUp(){
        std::vector<float> p;
        std::vector<float> d;

        p.push_back(1.0);
        p.push_back(2.0);
        p.push_back(3.0);

        d.push_back(0.0);
        d.push_back(0.8);
        d.push_back(0.6);

        JsonHelper::AddStringToJsonObject(json, "type", "robot");
        JsonHelper::AddStdFloatVectorToJsonObject(json, "position", p);
        JsonHelper::AddStdFloatVectorToJsonObject(json, "direction", d);
        JsonHelper::AddFloatToJsonObject(json, "speed", 30.0);
        JsonHelper::AddFloatToJsonObject(json, "radius", 1.0);
        JsonHelper::AddStringToJsonObject(json, "name", "robot");

        test_robo = new Robot(p);
        test_robo->SetDetails(json);

        JsonHelper::AddStringToJsonObject(pack, "type", "package");
        JsonHelper::AddStringToJsonObject(pack, "name", "package");
        JsonHelper::AddFloatToJsonObject(pack, "radius", 1.0);
        JsonHelper::AddStdFloatVectorToJsonObject(pack, "position", d);
        JsonHelper::AddStdFloatVectorToJsonObject(pack, "direction", d);

        test_pack = new Package(p);
        test_pack->SetDetails(pack);
    }
    virtual void TearDown(){ }
    Robot *test_robo;
    Package *test_pack;
    picojson::object pack = JsonHelper::CreateJsonObject();
    picojson::object json = JsonHelper::CreateJsonObject();
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RobotTest, GetterSetterTest){

    EXPECT_EQ("robot", test_robo->GetName()) << "Drone name is incorrect when 3 parameter constructor is run";

    vector<float> position;
    position.push_back(1.0);
    position.push_back(2.0);
    position.push_back(3.0);
    EXPECT_EQ(position, test_robo->GetPosition()) << "Drone position when specified as a parameter is not initialized correctly";

    vector<float> direction;
    direction.push_back(0.0);
    direction.push_back(0.8);
    direction.push_back(0.6);
    EXPECT_EQ(direction, test_robo->GetDirection()) << "Drone direction when specified as a parameter is not initialized correctly";

    EXPECT_EQ(-98, test_robo->GetId()) << "Drone Id is not initialized correctly when 3 parameter constructor is run";
    test_robo->SetId(31);
    EXPECT_EQ(31, test_robo->GetId()) << "SetId is incorrect";

    EXPECT_EQ(1, test_robo->GetRadius()) << "Drone radius is not initialized correctly when 3 parameter constructor is run";

    EXPECT_EQ(0, test_robo->GetVersion()) << "Dronte version is not initialized correctly when 3 parameter constructor is run";

    EXPECT_EQ(true, test_robo->IsDynamic()) << "Drone dynamic variable is not initialized correctly when 3 parameter constructor is run";

}
TEST_F(RobotTest, DeliveryEntityTests){
  EXPECT_EQ(false, test_robo->IsScheduled());
  EXPECT_EQ(false, test_robo->ScheduledPackage());
  EXPECT_FLOAT_EQ(10000, test_robo->GetRemainingBattery());
  test_robo->AssignPackage(test_pack);
  EXPECT_EQ(true, test_robo->ScheduledPackage());
}

}
