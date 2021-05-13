/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "gtest/gtest.h"
#include "entities/package.h"
#include "json_helper.h"

namespace csci3081{


/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PackageTest : public::testing::Test{
    protected:
    virtual void SetUp(){
        std::vector<float> p;

        p.push_back(1.0);
        p.push_back(2.0);
        p.push_back(3.0);

        JsonHelper::AddStringToJsonObject(json, "type", "package");
        JsonHelper::AddStringToJsonObject(json, "name", "package");
        JsonHelper::AddFloatToJsonObject(json, "radius", 1.0);
        JsonHelper::AddStdFloatVectorToJsonObject(json, "position", p);
        JsonHelper::AddStdFloatVectorToJsonObject(json, "direction", p);

        test_pack = new Package(p);
        test_pack->SetDetails(json);

        JsonHelper::AddStringToJsonObject(cust, "type", "customer");
        JsonHelper::AddStringToJsonObject(cust, "name", "customer");
        JsonHelper::AddFloatToJsonObject(cust, "radius", 1.0);
        JsonHelper::AddStdFloatVectorToJsonObject(cust, "position", p);
        JsonHelper::AddStdFloatVectorToJsonObject(cust, "direction", p);

        test_cust = new Customer(p);
        test_cust->SetDetails(cust);
        
    }
    virtual void TearDown(){  }
    Package *test_pack;
    Customer *test_cust;
    picojson::object json = JsonHelper::CreateJsonObject();
    picojson::object cust = JsonHelper::CreateJsonObject();
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F (PackageTest, Getters_and_Setters){
    EXPECT_EQ("package", test_pack->GetName()) << "Name getter incorrect";
    //position getter/setter
    std::vector<float> pos;
    pos.push_back(1.0);
    pos.push_back(2.0);
    pos.push_back(3.0);
    EXPECT_EQ(pos, test_pack->GetPosition()) << "incorrect position";
    std::vector<float> pos2;
    pos2.push_back(0.0);
    pos2.push_back(0.0);
    pos2.push_back(0.0);
    test_pack->SetPosition(pos2);
    EXPECT_EQ(pos2, test_pack->GetPosition()) << "position setter incorrect";
    //radius getter
    EXPECT_FLOAT_EQ(1.0, test_pack->GetRadius()) << "radius getter incorrect";
    //ID getter/setter
    EXPECT_EQ(-98, test_pack->GetId()) << "ID getter incorrect";
    test_pack->SetId(2);
    EXPECT_EQ(2, test_pack->GetId()) << "ID setter inccorect";
    //IsDynamic getter
    EXPECT_EQ(true, test_pack->IsDynamic()) << "incorrect IsDynamic";
    //Delivered getter
    EXPECT_EQ(false, test_pack->Delivered()) << "incorrect Delivered";
    //weight getter/setter
    EXPECT_FLOAT_EQ(0.0, test_pack->GetWeight()) << "Weight getter incorrect";
    test_pack->SetWeight(20.0);
    EXPECT_FLOAT_EQ(20.0, test_pack->GetWeight()) << "Weight setter incorrect";
    //customer getter/setter

    test_pack->AssignCustomer(test_cust);
    EXPECT_EQ(test_cust, test_pack->GetCustomer()) << "Customer getter/setter incorrect";

}

}
