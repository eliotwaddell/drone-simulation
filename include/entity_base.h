/**
 *@file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include "lib/vector3d.h"
#include "entities/path_context.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for creating entities.
 */
enum EntityType { UNDEFINED_ENTITY, DRONE, CUSTOMER, PACKAGE, ROBOT };

class EntityBase : public IEntity {
 public:

 /**
 * @brief The destructor for EntityBase
 **/
  virtual ~EntityBase() {}

    /**
    * @brief Returns the unique entity id.
    **/
    int GetId() const override { return id_; }

    /**
    * @brief Returns the name of an entity.
    **/
    const std::string& GetName() override { return name_; }

    /**
    * @brief Returns the entity's position.
    **/
    const std::vector<float>& GetPosition() const override { return position_; }

    /**
    * @brief Returns the entity's direction.
    **/
    const std::vector<float>& GetDirection() const override { return direction_; }

    /**
    * @brief Returns the entity's radius.
    **/
    float GetRadius() const override { return radius_; }

    /**
    * @brief Get version can be used to see whether or not a variable other than position or direction has changed.
    **/
    int GetVersion() const override { return 0; }

    /**
    * @brief Returns the type of entity
    **/
    EntityType GetType() { return t_; }

    /**
    * @brief This method specifies whether or not the entity is static (doesn't change often) or moves.
    **/
    bool IsDynamic() const override { return false; }


    /**
    * @brief Returns the picojson object that is used to create the entity
    **/
    picojson::object& GetDetails() override { return details_; }

    /**
    * @brief Sets the position of the entity
    * @param position: The vector of float values to set as the entity's position
    **/
    void SetPosition(std::vector<float> position) { position_ = position; }

    /**
    * @brief Sets the position of the entity
    * @param position: The Vector3D object that will be used to set the position vector
    **/
    void SetPosition(Vector3D position) { position_ = {position.x, position.y, position.z}; }

    /**
    * @brief Sets the direction of the entity
    * @param target: The Vector3D object that will be used to set the direction vector
    **/
    void SetDirection(Vector3D target) { direction_ = (target -= Vector3D(position_)).Normalize().ToVector(); }

    /**
    * @brief Sets the type of entity
    * @param t: the type to set the entity's type to
    **/
    void SetType(EntityType t) { t_ = t; }

    /**
    * @brief sets the picojson object of the entity
    * @param obj: the picojson object that details_ will be set to
    **/
    void SetDetails(const picojson::object& obj);

    /**
    * @brief Returns the position of the entity as a Vector3D
    **/
    Vector3D GetVPosition() { return Vector3D(position_); }

    /**
    * @brief Sets the id of the entity
    * @param id: The integer id to set the id_ of the entity to
    **/
    void SetId(int id) { id_ = id; }

    /**
    * @brief Prints out information about the entity
    **/
    void Print() const;

    /**
    * @brief returns a vector of observers of the entity
    **/
    std::vector<IEntityObserver*>* GetObservers() { return observers_; };

    /**
    * @brief Sets the vector of observers of the entity
    * @param observers: The vector of observers to set observers_ to
    **/
    void SetObservers(std::vector<IEntityObserver*>* observers) { observers_ = observers; }

    /**
    * @brief notifies the observers of the entity
    * @param type: string thats the type of notification
    * @param value: string thats the value of the notification
    **/
    void NotifyObservers(std::string type, std::string value);

    void NotifyObservers(std::string type, std::string value, picojson::object& obj);

    /**
    * @brief notifies the observers of the entity
    * @param type: string thats the type of notification
    * @param value: string thats the value of the notification
    * @param route: Vector3D thats the route to notify with
    **/
    void NotifyObservers(std::string type, std::string value, std::vector<Vector3D> route);

protected:
    EntityType t_ = UNDEFINED_ENTITY;
    picojson::object details_;
    std::string name_ = "undefined";
    int id_ = -99;
    float radius_ = 1.0;
    std::vector<float> position_;
    std::vector<float> direction_;
    std::vector<IEntityObserver*>* observers_;

};

}  // namespace csci3081

#endif  // ENTITY_BASE_H_
