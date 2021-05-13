/**
* @file green_decorator.h
**/
#ifndef GREEN_DECORATOR_H_
#define GREEN_DECORATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "delivery_decorator.h"
 /*******************************************************************************
  * Class Definitions
  ******************************************************************************/
  namespace csci3081{
  /**
  * @brief a wrapper class used to color drones and robots blue
  **/
  class GreenDecorator : public DeliveryDecorator
  {
    public:
      GreenDecorator(DeliveryEntity* d) : DeliveryDecorator(d){}
      void ColorEntity()
      {
        JsonHelper::AddStringToJsonObject(decorated_entity->GetDetails(), "color", "00ff00");
      }
  };




  }

  #endif
