//
// Created by User on 17.02.2022.
//
#include "Truck.h"
#include "Cargo.h"
#include <vector>
#include <queue>
using namespace std;
class HQ {
private:
    const int kM = 3;
    bool customGenTime_;
    double time_gen_next_cargo_;
    double custom_time_;
    queue<Truck*> truckQueue_;
    vector<Truck*> platforms_;
    vector<Cargo*> cargoQueue_;
public:
    HQ(bool condition, double time);
    ~HQ();
    int GetSizeTruckQueue();
    double GetSizeCargo(int id);
    bool CheckFreeSpaceForTruck();
    bool CheckIsAnyCargoToLoad();
    void AddNewCargo(Cargo* cargo);
    void AddTruckToQueue(Truck* truck);
    int AddTruckToPlatform();
    void DeleteTruckFromPlatform(int id);
    double GetTimeCargoGen();
    void SetTimeCargoGen(double time);
    Cargo* GetCargo(int id);
    int GetSizeQueue();
    int SelectDestinationDepot();
};

