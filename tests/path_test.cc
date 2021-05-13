/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entities/path_context.h"
#include "gtest/gtest.h"
#include <math.h>
#include <EntityProject/graph.h>
#include <iostream>

namespace csci3081{
/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class PathTest: public testing::Test{
    protected: 
        virtual void SetUp(){
            
            src1.push_back(0);
            src1.push_back(0);
            src1.push_back(0);

            dest1.push_back(85.0);
            dest1.push_back(0);
            dest1.push_back(40.0);

            actualDistance = 93.94;
            actualMidpoint.push_back(42.50);
            actualMidpoint.push_back(0);
            actualMidpoint.push_back(20.0);

            actualRoute.push_back(src1);
            stop1.push_back(0.85);
            stop1.push_back(7.92);
            stop1.push_back(0.40);
            actualRoute.push_back(stop1);
            stop2.push_back(1.7);
            stop2.push_back(15.68);
            stop2.push_back(0.80);
            actualRoute.push_back(stop2);
            stop3.push_back(2.55);
            stop3.push_back(23.28);
            stop3.push_back(1.2);
            actualRoute.push_back(stop3);
            stop4.push_back(3.40);
            stop4.push_back(30.72);
            stop4.push_back(1.60);
            actualRoute.push_back(stop4);            
        }
        virtual void TearDown() {}
        PathContext *pb = new PathContext("beeline");
        PathContext *pp = new PathContext("parabolic");
        //ParabolicRoute *pr;
        //const IGraph *graph_;
        //BeelineRoute *br;
        std::vector<float> src1;
        std::vector<float> dest1;
        float actualDistance;
        std::vector<float> actualMidpoint;
        std::vector<std::vector<float>> actualRoute;
        std::vector<float> stop1;
        std::vector<float> stop2;
        std::vector<float> stop3;
        std::vector<float> stop4;

};
/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F (PathTest, BeelineRouteTest){
    std::vector<std::vector<float>> route = pb->GetRoute(src1, dest1);
    std::vector<float> p1 = src1;
    p1.at(1) = p1.at(1) + 70;
    std::vector<float> p2 = dest1;
    p2.at(1) = p2.at(1) + 70;

    for(int i=0; i<3; i++){
        EXPECT_FLOAT_EQ(route.at(0).at(i), src1.at(i));
    }
    for(int i=0; i<3; i++){
        EXPECT_FLOAT_EQ(route.at(1).at(i), p1.at(i));
    }
    for(int i=0; i<3; i++){
        EXPECT_FLOAT_EQ(route.at(2).at(i), p2.at(i));
    }
    for(int i=0; i<3; i++){
        EXPECT_FLOAT_EQ(route.at(3).at(i), dest1.at(i));
    }
}
TEST_F (PathTest, ParabolicRouteTest){
    std::vector<std::vector<float>> route = pp->GetRoute(src1, dest1);
    float distanceFound = ParabolicRoute::Distance(src1, dest1);
    std::vector<float> midpointFound = ParabolicRoute::Midpoint(src1, dest1);
    //tests Distance function
    EXPECT_NEAR(actualDistance, distanceFound, 0.01);
    //tests midpoint function
    for(int i=0; i<3; i++){
        EXPECT_FLOAT_EQ(actualMidpoint.at(i), midpointFound.at(i));
    }
    for(int i=0; i<100; i+=20){
        for(int j=0; j<3; j++){
            //tests createRoute function
            EXPECT_NEAR(actualRoute.at(i/20).at(j), route.at(i/20).at(j), 0.01);
        }
    }
}

}
