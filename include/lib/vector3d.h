/**
* @file vector3d.h
**/
#ifndef VECTOR_3D_H_
#define VECTOR_3D_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <assert.h>
#include <math.h>
#include <ostream>
#include <iostream>

namespace csci3081 {

/*******************************************************************************
 * Struct Definition
 ******************************************************************************/

/**
* @brief Vector3D assists with the 3D vector math that needs to be done in our simulation
**/
struct Vector3D {
    float x, y, z;
    ~Vector3D() {}
    Vector3D(float x_ = 0, float y_ = 0, float z_ = 0) : x(x_), y(y_), z(z_) {}
    Vector3D(std::vector<float> vec) : x(vec[0]), y(vec[1]), z(vec[2]) {}
    Vector3D(const Vector3D& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; }


    /**
    * @brief overides the = operator for Vector3D objects
    * @param rhs: The other Vector object to set this equal to
    **/
    Vector3D operator=(const Vector3D& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    /**
    * @brief overrides the + operator for Vector3D objects
    * @param rhs: The other Vector to add onto this
    **/
    Vector3D operator+(const Vector3D& rhs) { return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z); }
    
    /**
    * @brief overrides the - operator for Vector3D objects
    * @param rhs: The other Vector to subtract from this
    **/
    Vector3D operator-(const Vector3D& rhs) { return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z); }
    
    /**
    * @brief overrides the * operator for Vector3D objects
    * @param scalar: a float value to multiply to each component of the Vector3D
    **/
    Vector3D operator*(float scalar) { return Vector3D(x * scalar, y * scalar, z * scalar); }
    
    /**
    * @brief overrides the / operator for Vector3D objects
    * @param scalar: a float value to have each component of the vector divided by
    **/
    Vector3D operator/(float scalar) { return Vector3D(x / scalar, y / scalar, z / scalar); }

    /**
    * @brief overrides the += operator for Vector3D objects
    * @param rhs: The other vector to add onto this
    **/
    Vector3D operator+=(const Vector3D& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    /**
    * @brief overrides the += operator for Vector3D objects
    * @param s: a scalar value to add onto each component of the Vector3D
    **/
    Vector3D operator+=(float s) {
        x += s;
        y += s;
        z += s;
        return *this;
    }

    /**
    * @brief overrides the -= operator for Vector3D objects
    * @param rhs: the other vector to subtract from this
    **/
    Vector3D operator-=(const Vector3D& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    /**
    * @brief overrides the -= operator for Vector3D objects
    * @param s: a scalar value to subtract from each componenet of the vector3D
    **/
    Vector3D operator-=(float s) {
        x -= s;
        y -= s;
        z -= s;
        return *this;
    }

    /**
    * @brief overrides the *= operator for Vector3D objects
    * @param s: a scalar to multiply to each compenent of the Vector3D
    **/
    Vector3D operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    /**
    * @brief sets each component of the Vector3D to the power given
    * @param n: the float value that is the power to raise each component to
    **/
    Vector3D pow(float n) {
        return Vector3D(std::pow(this->x, n), std::pow(this->y, n), std::pow(this->z, n));
    }

    /**
    * @brief overrides the == operator for Vector3D objects
    * @param rhs: The other vector to compare equals to
    **/
    bool operator==(const Vector3D rhs) { return (x == rhs.x && y == rhs.y && z == rhs.z); }
    
    /**
    * @brief overrides the != operator for Vector3D objects
    * @param rhs: the other vector to compare not equals to
    **/
    bool operator!=(const Vector3D rhs) { return (x != rhs.x || y != rhs.y || z != rhs.z); }

    /**
    * @brief overrides the << operator for Vector3D objects
    * @param os: The output stream to print the vector information to
    * @param v: The vector to print out the components to
    **/
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
      os << "<" << v.x << "," << v.y << "," << v.z << ">";
      return os;
    }

    /**
    * @brief Returns the magnitude of the vector
    **/
    float Magnitude() { return std::sqrt(x*x + y*y + z*z); }

    /**
    * @brief returns the Dot product between this and another vector
    * @param rhs: the other vector to dot multiply this by
    **/
	float Dot(const Vector3D& rhs) { return x*rhs.x + y*rhs.y + z*rhs.z; }


    /**
    * @brief Normalizes the vector internally
    **/
    Vector3D Normalize() {
        if (this->Magnitude() == 0) return *this;
        float l = this->Magnitude();
        this->x / l;
        this->y / l;
        this->z / l;
        return *this;
    }

    /**
    * @brief returns a vector of floats from the Vector3D object
    **/
    std::vector<float> ToVector() { std::vector<float> result = {x, y, z}; return result; }

    /**
    * @brief returns a vector of Vector3D objects that represent a route for a drone or robot to take
    * @param pts: a vector of vectors of floats that represent the points to convert to Vector3D objects
    **/
    static std::vector<Vector3D> BuildRoute(std::vector<std::vector<float>> pts) {
        std::vector<Vector3D> route;
        for (auto pt : pts) {
            route.push_back(Vector3D(pt));
        }
        return route;
    }

    /**
    * @brief prints out a legible version of the vector, in <x, y, z> form
    **/
    void Print() const { printf("<%f,%f,%f>\n", x, y, z); }

    /**
    * @brief Computes the distance between this vector and another Vector
    * @param rhs: the other vector to compute distance between
    **/
    float DistanceTo(const Vector3D& rhs) {
        return std::sqrt(std::pow(rhs.x-x,2)+std::pow(rhs.y-y,2)+std::pow(rhs.z-z,2));
    }

};

}  // namespace csci3081

#endif  // VECTOR_3_H_
#pragma once
