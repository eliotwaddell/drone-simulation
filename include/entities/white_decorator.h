/**
* @file white_decorator.h
**/
#ifndef WHITE_DECORATOR_H_
#define WHITE_DECORATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "delivery_decorator.h"
 /*******************************************************************************
  * Class Definitions
  ******************************************************************************/
  namespace csci3081{
  /**
  * @brief a wrapper class used to color drones and robots white
  **/
  class WhiteDecorator : public DeliveryDecorator
  {
    public:
      WhiteDecorator(DeliveryEntity* d) : DeliveryDecorator(d){}
      void ColorEntity()
      {
        JsonHelper::AddStringToJsonObject(decorated_entity->GetDetails(), "color", "ffffff");
      }
  };




  }

  #endif
