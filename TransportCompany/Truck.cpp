//
// Created by User on 17.02.2022.
//
#include "Truck.h"
using namespace std;
Truck::Truck(int id) {
    id_ = id;
    // Put all truck to the HQ in the beginning
    currentLocation_ = 6;
    // Since trucks will be in HQ. Arrival time to HQ will be 0
    time_event_finish_time_ = 0;
    // Set event type as truck arrival - In the beginning, arrival to the HQ
    event_type_ = 0;

    isReadyToLoad = false;
    isDriveAfterLoading = false;
}

Truck::~Truck() {
    while(!cargo_.empty()){
        Cargo* temp = cargo_.front();
        cargo_.pop();
        delete temp;
    }
}

// Returns the ID of Truck
int Truck::GetId() {
    return id_;
}

// Returns the current location of truck
int Truck::GetLocation() {
    return currentLocation_;
}

// Sets the current location of truck to its destination.
void Truck::SetCurrentLocation() {
    currentLocation_ = destination_;
}

// Returns the type of event which truck is gonna do
int Truck::GetEventType() {
    return event_type_;
}

// Returns if the truck is ready to load
bool Truck::GetIsReadyToLoad() {
    return isReadyToLoad;
}

// Returns if the truck is ready to go
bool Truck::GetIsReadyToGo() {
    return isReadyToGo;
}

// Returns the current capacity of the cargo inside of a truck
double Truck::GetSizeCargo() {
    return currentCapacity_;
}

// Returns if there is a cargo in the queue
bool Truck::GetInfoCargoQueue() {
    return cargo_.empty();
}

// Returns if the the truck is empty in other words available
bool Truck::GetInfoCargo() {
    bool isEmpty = (currentCapacity_ == 0) ? true : false;
    return isEmpty;
}

// Adding cargo to truck
void Truck::AddCargo(Cargo *cargo) {
    currentCapacity_ += cargo->GetSize();
    cargo_.push(cargo);
}

// Returns the ID of the first load found in the queue
int Truck::GetIdLoaded() {
    if (cargo_.empty()){
        return -1;
    }
    return cargo_.front()->GetId();
}

// Returns the first cargo waiting in the queue and pops it
Cargo *Truck::GetFirstCargo() {
    Cargo* temp = cargo_.front();
    cargo_.pop();
    return temp;
}

// Returns the finishing time of an event
double Truck::GetTimeEventFinishTime() {
    return time_event_finish_time_;
}

// Sets a new destination to the truck
void Truck::SetDestination(int destination) {
    destination_ = destination;
}

// Setting a new time event
void Truck::SetNewEvent(double time, int type) {
    time_event_finish_time_ = time;
    event_type_ = type;
}


void Truck::SetIsReadyToLoad(bool condition) {
    isReadyToLoad = condition;
}

// Sets whether truck is ready to leave or not
void Truck::SetIsReadyToGo(bool condition) {
    isReadyToGo = condition;
}

// checking if there is a place for next cargo
bool Truck::CheckSpace(double size) {
    bool canSendNewCargo = (kMaxCapacity >= currentCapacity_ + size) ? true : false;
    return canSendNewCargo;
}

// Truck can leave after loading
void Truck::SetIsDriveAfterLoading(bool condition) { //I can delete it maybe
    isDriveAfterLoading = condition;
}

// Returns whether the truck can leave or not
bool Truck::GetIsDriveAfterLoading() { //I can delete it maybe
    return isDriveAfterLoading;
}

// Resets the current capacity to default (0).
void Truck::FinishUnloading() {
    currentCapacity_ = 0;
}
