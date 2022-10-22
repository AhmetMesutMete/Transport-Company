//
// Created by User on 17.02.2022.
//
#pragma once
#include <vector>
using namespace std;
#include<iostream>
#include <random>
#include "SeedGen.h"
#include "Statistics.h"
#include "HQ.h"
#include "Truck.h"
#include "Depot.h"
using namespace std;
class Simulations {
private:
    double sim_time_ = 0;
    double initial_phase_time_ = 0;
    double max_sim_time_ = 0;
    bool custom_time_gen_cargo_ = false;
    double time_hq_cargo_gen_ = 0;
    double time_depot_cargo_gen_ = 0;
    vector<int> seeds_;
    bool initial_phase_;
    Statistics* statistics_;
    bool NO_EVENTTRIGGERED = true;
    vector<Truck*> truckVector_;
    vector<Depot*> depotVector_;
    const int kTruck = 8;
    const int kDepot = 6;
    HQ* HQ_; //Store HQ
    int start_value_;
    const double kM = 2147483647.0;
    static const int kA = 16807;
    static const int kQ = 127773;
    static const int kR = 2836;
public:
    Simulations(double initial_phase_time, double max_sim_time, bool custom_time_gen_cargo, double time_hq, double time_depot, vector<int> seeds, bool initial_phase_graph);
    ~Simulations();
    void Start();
    double UniformGenerator(int id);
    void updateSystemTime();
};

