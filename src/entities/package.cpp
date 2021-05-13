#include "json_helper.h"
#include "entities/package.h"

namespace csci3081 {

void Package::Deliver() {
  printf("Package %i delivered to customer %i\n", this->id_, customer_->GetId());
  this->SetPosition(Vector3D(0, -1000, 0));
  delivered_ = true;
}

void Package::Reschedule()
{
  vector<float> pos = this->GetPosition();
  pos.at(1) = 0;
  this->SetPosition(pos);
}

}  // namespace csci3081
