#include "factories/composite_factory.h"
#include "include/json_helper.h"

namespace csci3081 {

CompositeFactory::CompositeFactory() {}
CompositeFactory::~CompositeFactory() {}

void CompositeFactory::AddFactory(IEntityFactory* factory) {
  factories_.push_back(factory);
}

IEntity* CompositeFactory::CreateEntity(const picojson::object &val) {
  // Loop through all factories to create the desired entity type
  picojson::object config(val);
  std::cout << "Creating: " << JsonHelper::GetString(config, "type") << std::endl;
  for (IEntityFactory* factory : factories_) {
    IEntity* entity = factory->CreateEntity(val);
    if (entity) {
      return entity;
    }
  }
  std::cout << "Failed to make an entity" << std::endl;
  return NULL;
}

}  // namespace csci3081