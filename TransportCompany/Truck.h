//
// Created by User on 17.02.2022.
//
#pragma once
#include "Cargo.h"
#include <queue>
class Truck {
private:
    int id_;
    std::queue<Cargo *> cargo_;
    int currentLocation_;
    int destination_ = 6; // 0-5 regional depots and 6 is HQ
    const double kMaxCapacity = 10; // u = 10
    double currentCapacity_ = 0;
    double time_event_finish_time_;
    bool isReadyToLoad;
    int event_type_;
    bool isReadyToGo;
    bool isDriveAfterLoading;
public:
    Truck(int id);
    ~Truck();
    int GetId();
    int GetLocation();
    void SetCurrentLocation();
    int GetEventType();
    bool GetIsReadyToLoad();
    bool GetIsReadyToGo();
    double GetSizeCargo();
    bool GetInfoCargoQueue();
    bool GetInfoCargo();
    void AddCargo(Cargo* cargo);
    int GetIdLoaded();
    Cargo* GetFirstCargo();
    double GetTimeEventFinishTime();
    void SetDestination(int destination);
    void SetNewEvent(double time, int type);
    void SetIsReadyToLoad(bool condition);
    void SetIsReadyToGo(bool condition);
    bool CheckSpace(double size); // Check if there is a space for next cargo batch
    void SetIsDriveAfterLoading(bool condition);
    bool GetIsDriveAfterLoading();
    void FinishUnloading();
};



