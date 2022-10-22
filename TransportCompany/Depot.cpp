//
// Created by User on 17.02.2022.
//

#include "Depot.h"

Depot::Depot(bool condition, double time) {
    customGenTime_ = condition;
    custom_time_ = time;
}

Depot::~Depot() {
    while (!cargoQueue_.empty()){
        Cargo* temp;
        temp = cargoQueue_[0];
        cargoQueue_.erase(cargoQueue_.begin());
        delete temp;
    }
}

// Returns the size of Truck Queue
int Depot::GetSizeTruckQueue() {
    return truckQueue_.size();
}

// Returns the size of Cargo Queue
double Depot::GetSizeCargo(int id) {
    for (int i = 0; i < cargoQueue_.size(); i++)
        if (cargoQueue_[i]->GetId() == id) {
            return cargoQueue_[i]->GetSize(); //Returns the size of cargo batch
        }
    return -1;
}

//In here we check if there is a free platform
bool Depot::CheckFreeSpaceForTruck() {
    bool checkFree = (kM > platforms_.size()) ? true : false; //kM is the max number of platforms
    return checkFree;
}

// Check the size of cargoQueue so that we can learn
// if we have some cargo that we can load at the platform
bool Depot::CheckIsAnyCargoToLoad() {
    bool checkCargo = (cargoQueue_.size() > 0) ? true : false;
    return checkCargo;
}

// Get next cargo batch added to the queue
void Depot::AddCargo(Cargo *cargo) {
    cargoQueue_.push_back(cargo);
}

// Add Truck to queue
void Depot::AddTruckToQueue(Truck *truck) {
    truckQueue_.push(truck);
}

//Add first truck in queue to platform
int Depot::AddTruckToPlatform() {
    Truck* temp = truckQueue_.front();
    int id = temp->GetId();
    truckQueue_.pop();
    platforms_.push_back(temp);
    return id;
}

// Remove truck from the platform
void Depot::DeleteTruckFromPlatform(int id) {
    for (int i = 0; i < platforms_.size(); i++)
        if (platforms_[i]->GetId() == id) {
            platforms_.erase(platforms_.begin() + i);
        }
}

// Return time of new cargo generation
double Depot::GetTimeGenCargo() {
    return time_gen_next_cargo_;
}

// Here we set the time to generate the next cargo
void Depot::SetTimeGenCargo(double time) {
    time_gen_next_cargo_ = (time >= 0) ? time : (time_gen_next_cargo_+custom_time_);
}

//Return the cargo that we needed to load into truck
Cargo *Depot::GetCargo(int id) {
    for (int i = 0; i < cargoQueue_.size(); i++)
        if (cargoQueue_[i]->GetId() == id) {
            Cargo *temp = cargoQueue_[i];
            cargoQueue_.erase(cargoQueue_.begin() + i);
            return temp;
        }
}

// Return the size of cargoQueue
int Depot::GetSizeQueue() {
    return cargoQueue_.size();
}
