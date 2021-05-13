/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "gtest/gtest.h"
#include "entities/battery.h"
#include "json_helper.h"

namespace csci3081{

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class BatteryTest : public::testing::Test{
    protected:
    virtual void SetUp(){
      /*
        std::vector<float> p;
        std::vector<float>d;
        p.push_back(1.0);
        p.push_back(2.0);
        p.push_back(3.0);

        d.push_back(0.0);
        d.push_back(0.0);
        d.push_back(0.0);

        JsonHelper::AddStringToJsonObject(json, "type", "battery");
        JsonHelper::AddStringToJsonObject(json, "name", "battery");
        JsonHelper::AddFloatToJsonObject(json, "radius", 1.0);
        JsonHelper::AddStdFloatVectorToJsonObject(json, "position", p);
        JsonHelper::AddStdFloatVectorToJsonObject(json, "direction", d);
*/
        test_batt = new Battery();
        //test_batt->SetDetails(json);
    }
    virtual void TearDown(){  }
    Battery *test_batt;
    //picojson::object json = JsonHelper::CreateJsonObject();
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F (BatteryTest, InitializationTest){
    EXPECT_FLOAT_EQ(10000, test_batt->ChargeLeft());
    EXPECT_EQ(false, test_batt->IsDead());
}
TEST_F (BatteryTest, DepletionTest){
    for(int i=0; i<500; i++){
        test_batt->DepleteBattery(10.0);
    }
    EXPECT_FLOAT_EQ(5000, test_batt->ChargeLeft());
    for(int i=0; i<500; i++){
        test_batt->DepleteBattery(10.0);
    }
    EXPECT_FLOAT_EQ(0, test_batt->ChargeLeft());
    EXPECT_EQ(true, test_batt->IsDead());
}

}
