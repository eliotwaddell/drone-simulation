#include "entity_base.h"
#include "json_helper.h"

namespace csci3081 {

void EntityBase::SetDetails(const picojson::object& obj) {
    t_ = UNDEFINED_ENTITY;
    details_ = obj;
    name_ = (obj.find("name") != obj.end()) ? obj.find("name")->second.get<std::string>() : name_;
    id_++;
    radius_ = (obj.find("name") != obj.end()) ? (float) obj.find("radius")->second.get<double>() : radius_;
    direction_ = JsonHelper::GetStdFloatVector(obj, "direction");
}

void EntityBase::Print() const {
    printf("\x1B[32mEntity %i\033[0m \n", id_);
    std::cout << "name: " << name_ << std::endl;
    printf("position: <%f,%f,%f>\n\n",position_[0], position_[1], position_[2]);
}

void EntityBase::NotifyObservers(std::string type, std::string value)
{
  for(int i = 0; i < observers_->size(); i++)
	{
		picojson::object o;
		o["type"] = picojson::value(type);
		o["value"] = picojson::value(value);
		picojson::value v(o);
		observers_->at(i)->OnEvent(v, *this);
	}
}

void EntityBase::NotifyObservers(std::string type, std::string value, picojson::object& obj)
{
  for(int i = 0; i < observers_->size(); i++)
	{
		picojson::object o;
		o["type"] = picojson::value(type);
		o["value"] = picojson::value(value);
    o["details"] = picojson::value(obj);
		picojson::value v(o);
		observers_->at(i)->OnEvent(v, *this);
	}
}

void EntityBase::NotifyObservers(std::string type, std::string value, std::vector<Vector3D> route_)
{
  std::vector<std::vector<float>> encoded_route;
  for(int i = 0; i < route_.size(); i++)
  {
    encoded_route.push_back(route_.at(i).ToVector());
  }

  for(int i = 0; i < observers_->size(); i++)
  {
    picojson::object o;
    o["type"] = picojson::value(type);
    o["value"] = picojson::value(value);
    o["path"] = JsonHelper::EncodeArray(encoded_route);
    picojson::value v(o);
    observers_->at(i)->OnEvent(v, *this);
  }
}

}
