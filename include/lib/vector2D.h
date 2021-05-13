/**
* @file vector2D.h
*/
#ifndef VECTOR2D_H_
#define VECTOR2D_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/

namespace csci3081{

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
* @brief This class handles the operations of vector's that are 2D
*/
class Vector2D {
    public:

      /** 
      * @brief Constructor for the Vector2D class. Initializes x and z to 0 if parameters not specified
      * @param x_: float value for the x position
      * @param z_: float value for the z position
      */
        Vector2D(float x_ = 0, float z_ = 0) : x(x_), z(z_) {};

      /** 
      * @brief Destructor for the 2D vector
      */
        ~Vector2D();

      /** 
      * @brief returns the magnitude of the 2D vector
      */
        float GetMagnitude();

      /** 
      * @brief returns a vector 2D that has been normalized
      */
        Vector2D Normalize();

      /** 
      * @brief Adds the parameter vector to the 2D vector
      */
        void Add(Vector2D v);

      /** 
      * @brief returns the x value of the 2D vector
      */
        float Get_X();
        
      /** 
      * @brief returns the z value of the 2D vector
      */
        float Get_Z();

      /** 
      * @brief sets the x value of the 2D vector to the parameter
      */
        void Set_X(float x_);

      /** 
      * @brief sets the z value of the 2D vector to the parameter
      */
        void Set_Z(float z_);

        

    private:
        float x;
        float z;
};

} // namespace csci3081

#endif  //  VECTOR2D_H_