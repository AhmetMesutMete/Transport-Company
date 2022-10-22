//
// Created by User on 17.02.2022.
//

#include "Simulations.h"
#include <iostream>
using namespace std;
Simulations::Simulations(double initial_phase_time, double max_sim_time, bool custom_time_gen_cargo,
                         double time_hq, double time_depot, vector<int> seeds, bool initial_phase_graph) {
    cout << "The simulation just started" << endl;
    max_sim_time_ = max_sim_time;
    initial_phase_time_ = initial_phase_time;
    initial_phase_ = true;
    custom_time_gen_cargo_ = custom_time_gen_cargo;
    time_hq_cargo_gen_ = time_hq;
    time_depot_cargo_gen_ = time_depot;
    seeds_ = seeds;
    for (int i = 0; i < kTruck; i++){
        //We generate kTruck times Truck with ids starting from 0 to kTruck - 1
        Truck* temp = new Truck(i);
        truckVector_.push_back(temp);
    }

    for (int i = 0; i < kDepot; i++){

        Depot* temp = new Depot(custom_time_gen_cargo_, time_depot_cargo_gen_);
        depotVector_.push_back(temp);
    }
    HQ_ = new HQ(custom_time_gen_cargo_, time_hq_cargo_gen_);
    // Create an object of Statistics class
    statistics_ = new Statistics(initial_phase_graph);
}

Simulations::~Simulations() {
    delete HQ_;
    for (int i = 0; i < kDepot; i++)
        delete depotVector_[i];
    for (int i = 0; i < kTruck; i++)
        delete truckVector_[i];
    delete statistics_;
}

void Simulations::Start() {
    // Events:
    //-1 - Idle state
    // 0 - Truck Arrival
    // 1 - Loading
    // 2 - Unloading
    while (sim_time_ < max_sim_time_){

        NO_EVENTTRIGGERED = true;
        if (initial_phase_ == true && initial_phase_time_ >= sim_time_){
            initial_phase_ = false;
            statistics_->ResetStatistics();
            cout << "FYI, The stats have been reset." << endl;
            NO_EVENTTRIGGERED = false;
        }

        //Check Truck Arrival
        for (int i = 0; i < kTruck; i++){
            if (truckVector_[i]->GetEventType() == 0){
                if (truckVector_[i]->GetTimeEventFinishTime() == sim_time_){
                    truckVector_[i]->SetCurrentLocation();
                    //Checking location of truck
                    //Depots 0-5 (6 regional depots),   HQ - 6
                    //Since there is only one HQ then if a truck is at any regional depot it is for sure that
                    //the destination should be set to HQ. If it is in
                    if (truckVector_[i]->GetLocation() == 6){
                        cout << "Truck: " << i << " has arrived to HQ and time: " << sim_time_ << endl;
                        //Adding the truck with the given id to queue
                        HQ_->AddTruckToQueue(truckVector_[i]);
                        truckVector_[i]->SetNewEvent(-1, -1);
                    }else{
                        cout << "Truck: " << i << " has arrived to depot: " << truckVector_[i]->GetLocation() << " with time: " << sim_time_ << endl;
                        //Adding the truck with the given id to queue
                        depotVector_[truckVector_[i]->GetLocation()]->AddTruckToQueue(truckVector_[i]);
                        truckVector_[i]->SetNewEvent(-1, -1);
                    }
                    NO_EVENTTRIGGERED = false;
                }
            }
        }

        //Start of Service HQ
        if (HQ_->GetSizeTruckQueue() && HQ_->CheckFreeSpaceForTruck()){
            int id = HQ_->AddTruckToPlatform();
            // Check if it is empty or loaded (if currentcap == 0)
            if (truckVector_[id]->GetInfoCargo()){
                cout << "Truck: " << id << " has been added to one of the platforms in HQ and the truck is empty: " << endl;
                truckVector_[id]->SetIsReadyToLoad(true);
            }else{ // If truck is already loaded (full) then we calculate time and set unloading event
                // Tu = 0.7
                double time = sim_time_ + truckVector_[id]->GetSizeCargo() * 0.7; //0.7 = Tu
                cout << "Truck: " << id << " has been added to one of the platforms in HQ and the time of finish unloading: " << time << endl;
                truckVector_[id]->SetNewEvent(time, 2);
                statistics_->SaveUtilization(time - sim_time_, sim_time_);
            }
            NO_EVENTTRIGGERED = false;
        }

        //Start of Service Depot
        //Checking all depots
        for (int i = 0; i < kDepot; i++){
            if (depotVector_[i]->GetSizeTruckQueue() > 0 && depotVector_[i]->CheckFreeSpaceForTruck()){
                int id = depotVector_[i]->AddTruckToPlatform();
                //isEmpty
                if (truckVector_[id]->GetInfoCargo()){
                    cout << "Truck: " << id << " has been added to the platform of the depot: " << truckVector_[id]->GetLocation() << " and the truck is empty " << endl;
                    truckVector_[id]->SetIsReadyToLoad(true);
                }else{
                    double time = sim_time_ + truckVector_[id]->GetSizeCargo() * 0.7;
                    cout << "Truck: " << id << " has been added to the platform of the depot: " << i << "  and finish unloading time: " << time << endl;
                    truckVector_[id]->SetNewEvent(time, 2);
                    statistics_->SaveUtilization(time - sim_time_, sim_time_);
                }
                NO_EVENTTRIGGERED = false;
            }
        }

        //CheckTimeEndOfUnloadingEvent
        for (int i = 0; i < kTruck; i++){
            if (truckVector_[i]->GetEventType() == 2){
                if (truckVector_[i]->GetTimeEventFinishTime() == sim_time_){
                    // Truck finished unloading so we can set it to idle state
                    truckVector_[i]->SetNewEvent(-1, -1);
                    //Check if we have any cargo in the cargo
                    while (!(truckVector_[i]->GetInfoCargoQueue())){
                        statistics_->SaveTransportTime(truckVector_[i]->GetFirstCargo()->GetTimeTransport(sim_time_));
                    }
                    //Set current capacity to 0
                    truckVector_[i]->FinishUnloading();
                    // Truck is ready to load
                    truckVector_[i]->SetIsReadyToLoad(true);
                    cout << "Truck: " << i << " finished unloading." << endl;
                }
                NO_EVENTTRIGGERED = false;
            }
        }

        // Check the condition if we can Start Loading Cargo -- CanStartLoadingCargo
        //*********** Don't forgot to tell the change you made
        for (int i = 0; i < kTruck; i++){
            // IsReadyToLoad is true in the beginning and after endofunloading
            if (truckVector_[i]->GetIsReadyToLoad()){
                if (truckVector_[i]->GetLocation() == 6){
                    //Check if there is a cargo batch that can be loaded
                    if (HQ_->CheckIsAnyCargoToLoad()){
                        // Here I should change something I guess
                        //int id = (int)(UniformGenerator(6) * (6 - 0) + 0);
                        int id = HQ_->SelectDestinationDepot();
                        truckVector_[i]->SetDestination(id);
                        //counter of loaded time
                        double capacity_loaded_cargo = 0;
                        while (HQ_->GetSizeCargo(id) > 0){
                            if (truckVector_[i]->CheckSpace(HQ_->GetSizeCargo(id))){
                                capacity_loaded_cargo += HQ_->GetSizeCargo(id);
                                Cargo* cargo = HQ_->GetCargo(id);
                                statistics_->SaveCargoQueuingTime(cargo->GetTimeQueueing(sim_time_));
                                truckVector_[i]->AddCargo(cargo);
                            }
                            //If we don't have enough space or cargo batch
                            else{
                                //Truck is read to loading
                                truckVector_[i]->SetIsDriveAfterLoading(true);
                                break;
                            }
                        }
                        // Change the isreadytoload state to false since the loading already took place
                        truckVector_[i]->SetIsReadyToLoad(false);
                        //time = r * Tl
                        double time = 0.5 * capacity_loaded_cargo;
                        cout << "Truck: " << i << " is about to complete loading cargo in HQ with time: " << time << " loading: " << capacity_loaded_cargo << endl;
                        truckVector_[i]->SetNewEvent(time + sim_time_, 1);
                        statistics_->SaveUtilization(time, sim_time_);
                    }
                }else{
                    if (depotVector_[truckVector_[i]->GetLocation()]->CheckIsAnyCargoToLoad()){
                        truckVector_[i]->SetDestination(6);
                        double capacity_loaded_cargo = 0;
                        while (depotVector_[truckVector_[i]->GetLocation()]->GetSizeCargo(6) > 0){
                            if (truckVector_[i]->CheckSpace(depotVector_[truckVector_[i]->GetLocation()]->GetSizeCargo(6))){
                                capacity_loaded_cargo += depotVector_[truckVector_[i]->GetLocation()]->GetSizeCargo(6);
                                Cargo* cargo = depotVector_[truckVector_[i]->GetLocation()]->GetCargo(6);
                                statistics_->SaveCargoQueuingTime(cargo->GetTimeQueueing(sim_time_));
                                truckVector_[i]->AddCargo(cargo);
                            }
                            else{
                                truckVector_[i]->SetIsDriveAfterLoading(true);
                                break;
                            }
                        }
                        truckVector_[i]->SetIsReadyToLoad(false);
                        double time = 0.5 * capacity_loaded_cargo;
                        cout << "Truck: " << i << " is about to complete loading cargo in depot: " << truckVector_[i]->GetLocation() << " with time: " << time << endl;
                        truckVector_[i]->SetNewEvent(time + sim_time_, 1);
                        statistics_->SaveUtilization(time, sim_time_);
                    }
                }
                NO_EVENTTRIGGERED = false;
            }
        }

        //Check the time of EndOfLoadingEvent
        for (int i = 0; i < kTruck; i++){
            //EndOfLoading event - 1
            if (truckVector_[i]->GetEventType() == 1){
                if (truckVector_[i]->GetTimeEventFinishTime() == sim_time_){
                    if (truckVector_[i]->GetIsDriveAfterLoading()){
                        cout << "Truck: " << i << " is about to complete loading cargo and it is ready to go " << endl;
                        //to avoid collisions SetIsDriveAfterLoading should be set to false
                        truckVector_[i]->SetIsDriveAfterLoading(false);
                        truckVector_[i]->SetIsReadyToGo(true);
                    }else{ //If truck is not drive after loading then
                        if (truckVector_[i]->GetLocation() == 6){
                            if (truckVector_[i]->CheckSpace(HQ_->GetSizeCargo(truckVector_[i]->GetIdLoaded()))){
                                cout << "Truck: " << i << " ıs about to complete loading cargo  and it is ready to go." << endl;
                                // Since truck leaves we set it to idle state
                                truckVector_[i]->SetNewEvent(-1, -1);
                                // Truck is ready to go
                                truckVector_[i]->SetIsReadyToGo(true);
                            }else{
                                //Truck can leave
                                cout << "Truck: " << i << " is about to complete loading cargo  and it is ready to go " << endl;
                                truckVector_[i]->SetNewEvent(-1, -1);
                                truckVector_[i]->SetIsReadyToGo(true);
                            }
                        }else{
                            //Same Condition for Depot
                            if (truckVector_[i]->CheckSpace(depotVector_[truckVector_[i]->GetLocation()]->GetSizeCargo(truckVector_[i]->GetIdLoaded()))){
                                truckVector_[i]->SetNewEvent(-1, -1);
                                truckVector_[i]->SetIsReadyToGo(true);
                                cout << "Truck with id: " << i << " is about to complete loading cargo  and it is ready to go." << endl;
                            }
                            else{
                                truckVector_[i]->SetNewEvent(-1, -1);
                                truckVector_[i]->SetIsReadyToGo(true);
                                cout << "Truck with id: " << i << " is about to complete loading cargo  and it is ready to go " << endl;
                            }
                        }
                        NO_EVENTTRIGGERED = false;
                    }
                }
            }
        }

        //Check Condition if Truck can depart -- CanTruckDepart
        // Travelling time follows normal distribution
        for (int i = 0; i < kTruck; i++){
            if (truckVector_[i]->GetIsReadyToGo()){
                double time = 0;
                normal_distribution<double> distribution_traveling_time(20.0, 1.6);
                default_random_engine generator_traveling_time(seeds_[i]);
                //Changing seeds bcz default_random_engine prob. will generate the same values
                UniformGenerator(i);
                // Generation of time
                time = distribution_traveling_time(generator_traveling_time);
                statistics_->SaveUtilization(time, sim_time_);
                //If this condition met then we remove the truck from platform as its loaded
                if (truckVector_[i]->GetLocation() == 6){
                    HQ_->DeleteTruckFromPlatform(i);
                    cout << "Truck: " << i << " leaves HQ " << endl;
                }else{
                    //Same operation for Depot
                    depotVector_[truckVector_[i]->GetLocation()]->DeleteTruckFromPlatform(i);
                    cout << "Truck: " << i << " leaves depot: " << i << endl;
                }
                // Since truck is already left we can set the SetIsReadyToGo as false
                truckVector_[i]->SetIsReadyToGo(false);
                // The event for given truck now is arrival.
                // So as I defined event_type 0 as truck arrival type should be 0
                truckVector_[i]->SetNewEvent(sim_time_ + time, 0);
                cout << "Truck with id: " << i << " finish : " << sim_time_ + time << endl;
                NO_EVENTTRIGGERED = false;
            }
        }

        //CheckTimeGenerateCargoEvent
        if (HQ_->GetTimeCargoGen() == sim_time_){
            cout << "A cargo batch generated in HQ " << endl;
            //Here seed is 6 as HQ
            default_random_engine generator_cargo_weight(seeds_[6]);
            //Changing seed
            UniformGenerator(6);
            normal_distribution<double> distribution_hq_weight(2.0, 0.6);
            double size = distribution_hq_weight(generator_cargo_weight);
            //Here we calculate the id of cargo batch. In HQ we have IDs 0-5
            int id = (int)(UniformGenerator(6) * (6 - 0) + 0); // max = 6, min = 0, id = 6
            // In here I called the cargo batch object with the generated size above
            // Size will be set as I defined in the cargo.cpp
            Cargo* cargo = new Cargo(size, id, sim_time_);
            HQ_->AddNewCargo(cargo);
            statistics_->SaveHeadQuarterQueueSize(HQ_->GetSizeQueue());
            if (!custom_time_gen_cargo_){
                // if user didn't set custom time
                // we make generator with time chq = 2.2
                default_random_engine generator_cargo_time(seeds_[6]);
                UniformGenerator(6);
                // lambda = 1/ E[x] -> 1/2.2 = 0.45
                exponential_distribution<double> distribution_hq_cargo_time(0.45);
                HQ_->SetTimeCargoGen(distribution_hq_cargo_time(generator_cargo_time) + sim_time_);
            }else{
                // Please go to HQ class to check the expression I put
                HQ_->SetTimeCargoGen(-1);
            }
            NO_EVENTTRIGGERED = false;
        }


        for (int i = 0; i < kDepot; i++){
            if (depotVector_[i]->GetTimeGenCargo() == sim_time_){
                cout << "A cargo batch generated in depot: " << i << endl;
                default_random_engine generator_cargo_weight(seeds_[i]);
                UniformGenerator(i);
                normal_distribution<double> distribution_depot_weight(2.0, 0.6);
                double size = distribution_depot_weight(generator_cargo_weight);
                // There is one way from depots so id is set to 6 as it stands for HQ
                int id = 6;
                Cargo* cargo = new Cargo(size, id, sim_time_);
                depotVector_[i]->AddCargo(cargo);
                statistics_->SaveDepotQueueSize(depotVector_[i]->GetSizeQueue(), i);
                if (!custom_time_gen_cargo_){
                    default_random_engine generator_cargo_time(seeds_[i]);
                    UniformGenerator(i);
                    // lambda = 1/ E[x] -> 1/12.3= 0.081
                    exponential_distribution<double> distribution_hq_cargo_time(0.081);
                    depotVector_[i]->SetTimeGenCargo(distribution_hq_cargo_time(generator_cargo_time) + sim_time_);
                }else{
                    depotVector_[i]->SetTimeGenCargo(-1);
                }
                NO_EVENTTRIGGERED = false;
            }
        }
        //cout << "sim time before update: " << sim_time_ << endl;
        updateSystemTime();
        //cout << "sim time after update: " << sim_time_ << endl;
    }
    statistics_->PrintStatistics(sim_time_);


}

double Simulations::UniformGenerator(int id) {
    int h = seeds_[id] / kQ;
    seeds_[id] = kA * (seeds_[id] - kQ * h) - kR * h;
    if (seeds_[id] < 0) seeds_[id] = seeds_[id] + static_cast<int>(kM);
    return seeds_[id] / kM;
}

void Simulations::updateSystemTime() {
    double min_time = max_sim_time_;
    for (int i = 0; i < kTruck; i++){
        if (truckVector_[i]->GetTimeEventFinishTime() > -1)
            if(truckVector_[i]->GetTimeEventFinishTime() < min_time)
                min_time = truckVector_[i]->GetTimeEventFinishTime();

    }
    for (int j = 0; j < kDepot; j++){
        if (depotVector_[j]->GetTimeGenCargo() > -1)
            if(depotVector_[j]->GetTimeGenCargo() < min_time)
                min_time = depotVector_[j]->GetTimeGenCargo();
    }
    if (HQ_->GetTimeCargoGen() > -1)
        if (HQ_->GetTimeCargoGen() < min_time)
            min_time = HQ_->GetTimeCargoGen();

    sim_time_ = min_time;
}
