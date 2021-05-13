/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "gtest/gtest.h"
#include "entities/customer.h"
#include "json_helper.h"

namespace csci3081{

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class CustomerTest : public::testing::Test{
    protected:
    virtual void SetUp(){
        std::vector<float> p;
        std::vector<float>d;
        p.push_back(1.0);
        p.push_back(2.0);
        p.push_back(3.0);

        d.push_back(0.0);
        d.push_back(0.0);
        d.push_back(0.0);

        JsonHelper::AddStringToJsonObject(json, "type", "customer");
        JsonHelper::AddStringToJsonObject(json, "name", "customer");
        JsonHelper::AddFloatToJsonObject(json, "radius", 1.0);
        JsonHelper::AddStdFloatVectorToJsonObject(json, "position", p);
        JsonHelper::AddStdFloatVectorToJsonObject(json, "direction", d);

        test_cust = new Customer(p);
        test_cust->SetDetails(json);
    }
    virtual void TearDown(){  }
    Customer *test_cust;
    picojson::object json = JsonHelper::CreateJsonObject();
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F (CustomerTest, GetterSetterTest){
    EXPECT_EQ("customer", test_cust->GetName());
    std::vector<float> pos;
    pos.push_back(1.0);
    pos.push_back(2.0);
    pos.push_back(3.0);
    EXPECT_EQ(pos, test_cust->GetPosition());

    EXPECT_FLOAT_EQ(1.0, test_cust->GetRadius());

    EXPECT_EQ(-98, test_cust->GetId());
    test_cust->SetId(5);
    EXPECT_EQ(5, test_cust->GetId());
    EXPECT_EQ(0, test_cust->GetVersion());
    EXPECT_EQ(false, test_cust->IsDynamic());
}

}
