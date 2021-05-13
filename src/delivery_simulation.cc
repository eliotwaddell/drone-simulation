#include "delivery_simulation.h"
#include "entity_base.h"
#include "factories/drone_factory.h"
#include "factories/customer_factory.h"
#include "factories/package_factory.h"
#include "json_helper.h"
#include <limits>

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	entity_factory_ = new CompositeFactory();
	AddFactory(new DroneFactory());
	AddFactory(new CustomerFactory());
	AddFactory(new PackageFactory());
	AddFactory(new RobotFactory());
}

DeliverySimulation::~DeliverySimulation() {
	for (auto ent : entities_) {
		delete ent;
	}
	delete entity_factory_;
}

int DeliverySimulation::Uid() { id_++; return id_; }

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
    IEntity* ent = entity_factory_->CreateEntity(val);
    if (ent) {
	  EntityBase* b = dynamic_cast<EntityBase*>(ent);
	  b->SetId(this->Uid());
		b->SetObservers(&observers_);
	  b->Print();
      return ent;
    }
    return NULL;
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	entity_factory_->AddFactory(factory);
}

void DeliverySimulation::AddEntity(IEntity* entity) {
	// Add to entity vector
	if (entity) {
		entities_.push_back(entity);
	} else {
		std::cout << "Null entity attempted to be added" << std::endl;
		return;
	}
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	graph_ = graph;
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	Package* p = dynamic_cast<Package*>(package);
	Customer* c = dynamic_cast<Customer*>(dest);
	Drone* d = nullptr;
	Robot* r = nullptr;
	float min = std::numeric_limits<float>::infinity();
	for (auto e : entities_) {
		d = dynamic_cast<Drone*>(e);
		if (d && (!d->IsScheduled())) {
			std::cout <<"Drone casted! " <<d->GetId()<<"\n";
			float score = (d->GetVPosition() - p->GetVPosition()).Magnitude();
			if (score < min) min = score;
			scheduled_drone.push_back(d);
			break;
		}
		else{
			r = dynamic_cast<Robot*>(e);
			if (r && (!r->IsScheduled())){
				std::cout << "Robot casted!\n";
				float score = (r->GetVPosition() - r->GetVPosition()).Magnitude();
				if (score < min) min = score;
				scheduled_robot.push_back(r);
				break;
			}
		}
	}

	if (d){
		path_ = new PathContext(d->GetPath());
		path_->SetGraph(graph_);
		d->SetGraph(graph_);
		auto route = path_->GetRoute(scheduled_drone.at(scheduled_drone.size() - 1)->GetPosition(), p->GetPosition());
		p->AssignCustomer(c);
		scheduled_drone.at(scheduled_drone.size() - 1)->SetGraph(graph_);
		scheduled_drone.at(scheduled_drone.size() - 1)->AssignPackage(p);
		scheduled_drone.at(scheduled_drone.size() - 1)->SetGraph(graph_);
		scheduled_drone.at(scheduled_drone.size() - 1)->SetRoute(Vector3D::BuildRoute(route));
		p->NotifyObservers("notify", "scheduled");
	}
	if (r){
		auto path = graph_->GetPath(scheduled_robot.at(scheduled_robot.size() - 1)->GetPosition(), p->GetPosition());
		p->AssignCustomer(c);
		scheduled_robot.at(scheduled_robot.size() - 1)->SetGraph(graph_);
		scheduled_robot.at(scheduled_robot.size() - 1)->AssignPackage(p);
		scheduled_robot.at(scheduled_robot.size() - 1)->SetRoute(Vector3D::BuildRoute(path));
		p->NotifyObservers("notify", "scheduled");
	}
	if (!(r || d)){
		unscheduled_customer.push_back(c);
		unscheduled_package.push_back(p);
	}
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) { observers_.push_back(observer); }

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) { observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end()); }

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::RemoveEntity(IEntity* entity) {
  for (int i = 0; i < entities_.size(); i++) {
    if (entities_[i]->GetId() == entity->GetId()) {
      entities_.erase(entities_.begin() + i);
      return;
    }
  }
}

void DeliverySimulation::Update(float dt) {
	auto drone_it = scheduled_drone.begin();
	auto robot_it = scheduled_robot.begin();
	for (Drone* d : scheduled_drone) {
		d->Update(dt);
		if(d->GetRemainingBattery() <= 0)
		{
			unscheduled_package.push_back(d->GetPackage());
			unscheduled_customer.push_back(d->GetPackage()->GetCustomer());
			scheduled_drone.erase(drone_it);
		}
		else
		{
			drone_it++;
		}
	}
	for (Robot* r : scheduled_robot){
		r->Update(dt);
		if(r->GetRemainingBattery() <= 0)
		{
			unscheduled_package.push_back(r->GetPackage());
			unscheduled_customer.push_back(r->GetPackage()->GetCustomer());
			scheduled_robot.erase(robot_it);
		}
		else
		{
			robot_it++;
		}
	}
	for (int i = 0; i<unscheduled_package.size(); i++){
		ScheduleDelivery(unscheduled_package.at(i), unscheduled_customer.at(i));
		unscheduled_package.erase(unscheduled_package.begin() + i);
		unscheduled_customer.erase(unscheduled_customer.begin() + i);
	}
}


// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {

	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				std::cout << "Test rata" << std::endl;
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
