/**
* @file path_context.h
**/

#ifndef PATH_CONTEXT_H_
#define PATH_CONTEXT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "path.h"

namespace csci3081{

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief Path context is the intermediate class between Drone/DeliverySimulation and 
* path. It chooses which route to send back depending on the path specified. Allows
* for proper implementation of the strategy pattern.
**/
class PathContext {

    private:
        Path *path_;
        const entity_project::IGraph *graph_;
 
    public:

        /**
        * @brief The Constructor for PathContext that takes in the path type
        * @param path: A type of path for the drone to take, represented as a string
        **/
        PathContext(std::string path) {
            std::cout <<path<<std::endl;
            if (path == "parabolic"){
			    path_ = new ParabolicRoute();
            } else{
            if (path == "beeline"){
                path_ = new BeelineRoute();
            } else {
                //Default path to take is the smart route
                path_ = new SmartRoute();
                path_->SetGraph(graph_);
            }
            }
        }

        /**
        * @brief sets the graph of the PathContext. Allows for proper implementation of smart route
        * @param graph: The IGraph* that will be used to get the smart route
        **/
        void SetGraph(const entity_project::IGraph* graph){
            graph_ = graph;
            path_->SetGraph(graph_);
       }

        /**
        * @brief Depending on the path type specified, returns a vector of points for the drone to take
        * @param src: the source point of the drone, represented as a vector of floats
        * @param dest: the destination of the drone, represented as a vector of floats
        **/
        const std::vector< std::vector<float> > 
            GetRoute(std::vector<float> src, std::vector<float> dest){
                return path_->CreateRoute(src, dest);
            }
};

}       //  namespace csci3081

#endif  //  PATH_CONTEXT_H_