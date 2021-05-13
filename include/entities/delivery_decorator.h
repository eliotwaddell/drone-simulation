/**
* @file delivery_decorator.h
**/
#ifndef DELIVERY_DECORATOR_H_
#define DELIVERY_DECORATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "delivery_entity.h"
 #include "json_helper.h"
 /*******************************************************************************
  * Class Definitions
  ******************************************************************************/
  namespace csci3081{
  /**
  * @brief a wrapper class used to color drones and robots based on if they
  * are idle, moving to package, or moving to customer.
  **/
  class DeliveryDecorator : public DeliveryEntity
  {
    public:
      DeliveryDecorator(DeliveryEntity* d)
      {
        decorated_entity = d;
      }
    picojson::object& GetDetails() override
    {
      return decorated_entity->GetDetails();
    }

    protected:
      DeliveryEntity* decorated_entity;
  };




  }

  #endif
