//
// Created by User on 17.02.2022.
//
#include "Truck.h"
#include "Cargo.h"
#include <vector>
#include <queue>
using namespace std;
class Depot {
private:
    const int kM = 1;
    queue<Truck*> truckQueue_;
    vector<Truck*> platforms_;
    vector<Cargo*> cargoQueue_; // vector but I used like queue
    double time_gen_next_cargo_;
    bool customGenTime_;
    double custom_time_;
public:
    Depot(bool condition, double time);
    ~Depot();
    int GetSizeTruckQueue();
    double GetSizeCargo(int id);
    bool CheckFreeSpaceForTruck();
    bool CheckIsAnyCargoToLoad();
    void AddCargo(Cargo* cargo);
    void AddTruckToQueue(Truck* truck);
    int AddTruckToPlatform();
    void DeleteTruckFromPlatform(int id);
    double GetTimeGenCargo();
    void SetTimeGenCargo(double time);
    Cargo* GetCargo(int id);
    int GetSizeQueue();
};

