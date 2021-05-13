/**
* @file path.h
**/
#ifndef PATH_H_
#define PATH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <string>
#include <lib/vector3d.h>
#include <EntityProject/graph.h>
#include <math.h>
#include <iostream>

namespace csci3081{

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief Path is the interface for each different type of path. Beeline, Smart, and parabolic
* paths all inherit from Path and override the CreateRoute function
**/
class Path {

    protected:
        const entity_project::IGraph *graph_;

    public:

        /**
        * @brief Sets the graph for the Path, used to create the smart route 
        * @param graph: The IGraph* used to create the smart route
        **/
        void SetGraph(const entity_project::IGraph* graph){
                graph_ = graph;
        }

        /**
        * @brief A virtual method for all children to override. Returns a vector of points to be followed
        * for the drone to reach its destination
        * @param src: The inital source point for the drone to start at 
        * @param dest: The destination for the drone
        **/
        virtual const std::vector< std::vector<float> >
            CreateRoute(std::vector<float> src, std::vector<float> dest) const = 0;
};


/**
* @brief The SmartRoute class inherits from path and overrides the CreateRoute function
* it is used to create the smart route for the drone to take using the graph
**/
class SmartRoute : public Path {
    public:

    /**
    * @brief Creates a smart route using the graph_ GetPath method
    * @param src: The inital source point for the drone to start at 
    * @param dest: The destination for the drone
    **/
    const std::vector< std::vector<float> >
        CreateRoute(std::vector<float> src, std::vector<float> dest) const override {
            return graph_->GetPath(src, dest);
        }

};

/**
* @brief The beeline roue inherits from path and overrides the CreateRoute function
* It is used to create a beeline route for the drone to take
**/
class BeelineRoute : public Path {
    public:

    /**
    * @brief Returns a vector of points for the drone to take to create a beeline route from 
    * its location to the destination
    * @param src: The inital source point for the drone to start at 
    * @param dest: The destination for the drone
    **/
    const std::vector< std::vector<float> >
        CreateRoute(std::vector<float> src, std::vector<float> dest) const override {
            std::vector< std::vector<float> > route;
            std::vector<float> point = src;
            Vector3D x;
            //starting point
            route.push_back(src);
            x = Vector3D(route.at(0));
            x.Print();


            //go up 70 units
            point.at(1) = point.at(1) + 70;

            route.push_back(point);
            x = Vector3D(route.at(1));
            x.Print();

            //move to destination point
            point = dest;
            point.at(1) = point.at(1) + 70;

            route.push_back(point);
            x = Vector3D(route.at(2));
            x.Print();

            //move down to destination
            route.push_back(dest);
            x = Vector3D(route.at(3));
            x.Print();

            std::cout <<route.size()<<std::endl;
            return route;
        }
};


/**
* @brief the parabolic route inherits from the path class and overrides the GetRoute funciton
* It is used to create a parabolic route for the drone to take to reach a destination
**/
class ParabolicRoute : public Path {

    public:

    /**
    * @brief Returns the distance between two points
    * @param x: one point, represented by a vector of floats
    * @param y: another point, represented by a vector of floats
    **/
    static float Distance(std::vector<float> x, std::vector<float> y){
        float inside =
          pow( (x.at(0) - y.at(0)), 2 )  +
          pow( (x.at(1) - y.at(1)), 2 )  +
          pow( (x.at(2) - y.at(2)), 2 );
        float distance = pow(inside, 0.5);
        return distance;
    }

    /**
    * @brief Returns the midpoint between two points
    * @param pt1: one of the points to take the midpoint of, represented as a vector of floats
    * @param pt2: the other point to take the midpoint of, represented as a vector of floats
    **/
    static std::vector<float> Midpoint(std::vector<float> pt1, std::vector<float> pt2){
            std::vector<float> midpoint;
            midpoint.push_back( (pt1.at(0) + pt2.at(0) ) / 2);
            midpoint.push_back( (pt1.at(1) + pt2.at(1) ) / 2);
            midpoint.push_back( (pt1.at(2) + pt2.at(2) ) / 2);
            return midpoint;
    }

    /**
    * @brief Returns the y value to be added to a point between two points in order for it to take
    * a smooth parabolic arc
    * @param v0: the source point along the path, represented as a vector of floats
    * @param v: The current point along the path, represented as a vector of floats
    * @param vm: The midpoint between the two end points of the path, represented as a vector of floats
    **/
    static float Y_Value(std::vector<float> v0, std::vector<float> v, std::vector<float> vm){
        float y = (1 -
            (
                pow( ParabolicRoute::Distance(v, vm), 2) /
                pow( ParabolicRoute::Distance(v0, vm), 2)
            )
        ) * 200;
        return y;
    }

    /**
    * @brief Creates a parabolic route for the drone to take using 100 points and a max height of 200
    * @param src: The source point to start the path at, represented as a vector of floats
    * @param dest: The destination of the drone, represented as a vector of floats
    **/    
    const std::vector< std::vector<float> >
        CreateRoute(std::vector<float> src, std::vector<float> dest) const override{
            std::vector< std::vector<float> > route;
            Vector3D src_3d(src);
            Vector3D dest_3d(dest);
            Vector3D distance(dest_3d - src_3d);
            Vector3D step_size_vector = distance/100;
            std::vector<float> midpoint = ParabolicRoute::Midpoint(src, dest);
            std::vector<float> point = src;
            Vector3D pointVec = Vector3D(src);

            for (int t = 0; t<=100; t++){
                point = (pointVec + (step_size_vector * t)).ToVector();
                route.push_back(point);
            }
            for (int i = 0; i<=100; i++){
              route.at(i).at(1) = route.at(i).at(1) + ParabolicRoute::Y_Value(src, route.at(i), midpoint);
            }


            return route;
        }
};


}   //  namespace csci3081

#endif // PATH_H_
