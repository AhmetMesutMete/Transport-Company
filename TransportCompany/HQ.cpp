//
// Created by User on 17.02.2022.
//

#include "HQ.h"

HQ::HQ(bool condition, double time) {
    customGenTime_ = condition;
    custom_time_ = time;
}

HQ::~HQ() {
    while (!cargoQueue_.empty())
    {
        Cargo* temp = cargoQueue_[0];
        cargoQueue_.erase(cargoQueue_.begin());
        delete temp;
    }
}

// Return the size of Truck Queue
int HQ::GetSizeTruckQueue() {
    return truckQueue_.size();
}

// Return the size of the cargo batch
double HQ::GetSizeCargo(int id) {
    for (int i = 0; i < cargoQueue_.size(); i++)
        if (cargoQueue_[i]->GetId() == id) {
            return cargoQueue_[i]->GetSize();
        }
    return -1;
}

// Check if there is a free space in the platforms
bool HQ::CheckFreeSpaceForTruck() {
    bool checkFree = (kM > platforms_.size()) ? true : false;
    return checkFree;
}

// Check if there is some cargo that can be loaded
bool HQ::CheckIsAnyCargoToLoad() {
    bool checkCargo = (cargoQueue_.size() > 0) ? true : false;
    return checkCargo;
}

// Getting the next cargo batch
void HQ::AddNewCargo(Cargo *cargo) {
    cargoQueue_.push_back(cargo);
}

// Add truck to the queue
void HQ::AddTruckToQueue(Truck *truck) {
    truckQueue_.push(truck);
}

// Add the first truck of truckQueue to a platform
int HQ::AddTruckToPlatform() {
    Truck* temp = truckQueue_.front();
    int id = temp->GetId();
    truckQueue_.pop();
    platforms_.push_back(temp);
    return id;
}

// Delete Truck from the platform
void HQ::DeleteTruckFromPlatform(int id) {
    for (int i = 0; i < platforms_.size(); i++)
        if (platforms_[i]->GetId() == id) {
            platforms_.erase(platforms_.begin() + i);
        }
}

// Return next cargo generation time
double HQ::GetTimeCargoGen() {
    return time_gen_next_cargo_;
}

// Set the new cargo generation time
void HQ::SetTimeCargoGen(double time) {
    time_gen_next_cargo_ = (time >= 0) ? time : (time_gen_next_cargo_+custom_time_);
}

// Get the cargo that we needed to load to a truck
Cargo *HQ::GetCargo(int id) {
    for (int i = 0; i < cargoQueue_.size(); i++)
        if (cargoQueue_[i]->GetId() == id) {
            Cargo *temp = cargoQueue_[i];
            cargoQueue_.erase(cargoQueue_.begin() + i);
            return temp;
        }
}
int HQ::SelectDestinationDepot(){
    return cargoQueue_.front()->GetId();
}
// Returns the cargo queue size
int HQ::GetSizeQueue() {
    return cargoQueue_.size();
}
