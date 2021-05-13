#include "factories/customer_factory.h"
#include "entities/customer.h"
#include "json_helper.h"

namespace csci3081 {

CustomerFactory::CustomerFactory() {}
CustomerFactory::~CustomerFactory() {}

IEntity* CustomerFactory::CreateEntity(const picojson::object &val) {
  Customer* customer = NULL;
  picojson::object config(val);
  if (config["type"].get<std::string>() == "customer") {
    printf("In Customer Factory\n");
    auto init_pos = JsonHelper::GetStdFloatVector(config, "position");
    customer = new Customer(init_pos);
    customer->SetDetails(val);
  }
  return customer;
}

}  // namespace csci3081