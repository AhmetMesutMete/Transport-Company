//
// Created by User on 17.02.2022.
//
#pragma once
#include <vector>
using namespace std;
class Statistics {
private:
    double hq_queue_size_ = 0;
    double countSaveSizeHQ = 0;
    vector<double> depotQueueSize_; // Since there is 6 depots
    vector<double> countSaveDepotQueueSize_;
    double time_sum_cargoQueuing_ = 0;
    double countSaveCargoQueuing = 0;
    double time_sum_cargoTransport_ = 0;
    double countSaveCargoTransportTime_ = 0;
    double time_sum_time_of_utilization_ = 0;
    bool initial_phase_graph_;
public:
    Statistics(bool initial_phase_graph);
    ~Statistics() = default;
    void SaveHeadQuarterQueueSize(unsigned size);
    void SaveDepotQueueSize(unsigned size, int id_depot);
    void SaveCargoQueuingTime(double time);
    void SaveTransportTime(double time);
    void SaveUtilization(double time, double simulation_time);
    void PrintStatistics(double time);
    void ResetStatistics();
};

