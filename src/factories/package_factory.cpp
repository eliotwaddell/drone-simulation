#include "factories/package_factory.h"
#include "entities/package.h"
#include "json_helper.h"

namespace csci3081 {

PackageFactory::PackageFactory() {}
PackageFactory::~PackageFactory() {}

IEntity* PackageFactory::CreateEntity(const picojson::object &val) {
  Package* package = NULL;
  picojson::object config(val);
  if (config["type"].get<std::string>() == "package") {
    printf("In Package Factory\n");
    auto init_pos = JsonHelper::GetStdFloatVector(config, "position");
    package = new Package(init_pos);
    package->SetDetails(val);
  }
  return package;
}

}  // namespace csci3081