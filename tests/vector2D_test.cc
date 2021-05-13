/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/vector2D.h"
#include "gtest/gtest.h"
#include <math.h>


namespace csci3081{

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class Vector2DTest: public testing::Test{
    protected: 
        virtual void SetUp(){
            EmptyParam = Vector2D();
            OneParameter = Vector2D(3.7);
            TwoParameter = Vector2D(-4.2, 5.8);
        }
        virtual void TearDown() {}
        Vector2D EmptyParam;
        Vector2D OneParameter;
        Vector2D TwoParameter;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
/*
TEST_F (Vector2DTest, DefaultConstructor){
    EXPECT_FLOAT_EQ(EmptyParam.Get_X(), 0.0);
    EXPECT_FLOAT_EQ(EmptyParam.Get_Z(), 0.0);
}

TEST_F (Vector2DTest, OneParameterConstructor){
    EXPECT_FLOAT_EQ(OneParameter.Get_X(), 3.7);
    EXPECT_FLOAT_EQ(OneParameter.Get_Z(), 0.0);
}

TEST_F (Vector2DTest, TwoParameterConstructor){
    EXPECT_FLOAT_EQ(TwoParameter.Get_X(), -4.2);
    EXPECT_FLOAT_EQ(TwoParameter.Get_Z(), 5.8);
}

TEST_F(Vector2DTest, GetterSetterTests){
    TwoParameter.Set_X(-20);
    TwoParameter.Set_Z(15);
    EXPECT_FLOAT_EQ(TwoParameter.Get_X(), -20);
    EXPECT_FLOAT_EQ(TwoParameter.Get_Z(), 15);   
}

TEST_F(Vector2DTest, GetMagnitudeTests){
    TwoParameter.Set_X(-20);
    TwoParameter.Set_Z(15);
    EXPECT_FLOAT_EQ(TwoParameter.GetMagnitude(), 25);
    EXPECT_FLOAT_EQ(EmptyParam.GetMagnitude(), 0.0);
    EXPECT_FLOAT_EQ(OneParameter.GetMagnitude(), 3.7);
}

TEST_F(Vector2DTest, NormalizeTests){
    TwoParameter.Set_X(-20);
    TwoParameter.Set_Z(15);

    Vector2D norm1 = TwoParameter.Normalize();
    EXPECT_FLOAT_EQ(norm1.Get_X(), -0.8);
    EXPECT_FLOAT_EQ(norm1.Get_Z(), 0.6);

    Vector2D norm2 = EmptyParam.Normalize();
    EXPECT_FLOAT_EQ(norm2.Get_X(), 0);
    EXPECT_FLOAT_EQ(norm2.Get_Z(), 0);

    Vector2D norm3 = OneParameter.Normalize();
    EXPECT_FLOAT_EQ(norm3.Get_X(), 1);
    EXPECT_FLOAT_EQ(norm3.Get_Z(), 0);
}

TEST_F(Vector2DTest, AddTests){
    TwoParameter.Set_X(-20);
    TwoParameter.Set_Z(15);
    TwoParameter.Add(Vector2D(20, -15));
    EXPECT_FLOAT_EQ(TwoParameter.Get_X(), 0);
    EXPECT_FLOAT_EQ(TwoParameter.Get_Z(), 0);
}
*/
}
