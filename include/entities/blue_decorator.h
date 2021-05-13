/**
* @file blue_decorator.h
**/
#ifndef BLUE_DECORATOR_H_
#define BLUE_DECORATOR_H_
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
  class BlueDecorator : public DeliveryDecorator
  {
    public:
      BlueDecorator(DeliveryEntity* d) : DeliveryDecorator(d){}
      void ColorEntity()
      {
        JsonHelper::AddStringToJsonObject(decorated_entity->GetDetails(), "color", "0000ff");
      }
  };




  }

  #endif
