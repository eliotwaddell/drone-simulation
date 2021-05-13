/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/vector3d.h"
#include "gtest/gtest.h"
#include <math.h>


namespace csci3081{


/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class Vector3DTest: public testing::Test{
    protected: 
        virtual void SetUp(){
            vec0 = Vector3D();
            vec1 = Vector3D(1.5, 2.5, 3.0);
            vec2 = Vector3D(0.5, 0.5, 1.0);
        }
        virtual void TearDown() {}
        Vector3D vec0;
        Vector3D vec1; 
        Vector3D vec2;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F (Vector3DTest, ConstructorTest){
    EXPECT_FLOAT_EQ(vec0.x, 0.0);
    EXPECT_FLOAT_EQ(vec0.y, 0.0);
    EXPECT_FLOAT_EQ(vec0.z, 0.0);

    EXPECT_FLOAT_EQ(vec1.x, 1.5);
    EXPECT_FLOAT_EQ(vec1.y, 2.5);
    EXPECT_FLOAT_EQ(vec1.z, 3.0);
}
TEST_F (Vector3DTest, OperationTest){
    vec1 += 0.5;
    EXPECT_FLOAT_EQ(vec1.x, 2.0);
    EXPECT_FLOAT_EQ(vec1.y, 3.0);
    EXPECT_FLOAT_EQ(vec1.z, 3.5);
    vec1 -= 1.5;
    EXPECT_FLOAT_EQ(vec1.x, 0.5);
    EXPECT_FLOAT_EQ(vec1.y, 1.5);
    EXPECT_FLOAT_EQ(vec1.z, 2.0);
    vec1 *= 2;
    EXPECT_FLOAT_EQ(vec1.x, 1.0);
    EXPECT_FLOAT_EQ(vec1.y, 3.0);
    EXPECT_FLOAT_EQ(vec1.z, 4.0);
    vec1 = vec1.pow(2);
    EXPECT_FLOAT_EQ(vec1.x, 1.0);
    EXPECT_FLOAT_EQ(vec1.y, 9.0);
    EXPECT_FLOAT_EQ(vec1.z, 16.0);
}
TEST_F (Vector3DTest, VectorOpTest){
    vec1 = vec1 + vec2;
    EXPECT_FLOAT_EQ(vec1.x, 2.0);
    EXPECT_FLOAT_EQ(vec1.y, 3.0);
    EXPECT_FLOAT_EQ(vec1.z, 4.0);
    vec1 = vec1 - vec2;
    EXPECT_FLOAT_EQ(vec1.x, 1.5);
    EXPECT_FLOAT_EQ(vec1.y, 2.5);
    EXPECT_FLOAT_EQ(vec1.z, 3.0);

    EXPECT_EQ(false, vec1 == vec2); 
    EXPECT_EQ(true, vec1 != vec2);
    vec1 *= 0;
    EXPECT_EQ(true, vec1 == vec0);
    EXPECT_EQ(false, vec1 != vec0);
}

}
