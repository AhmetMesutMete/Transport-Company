//
// Created by User on 17.02.2022.
//
#include "Statistics.h"
#include <iostream>
#include <fstream>
Statistics::Statistics(bool initial_phase_graph) {
    for (int i = 0; i < 6; i++){
        // Set each depotQueue s size to 0
        depotQueueSize_.push_back(0);
        countSaveDepotQueueSize_.push_back(0);
    }
    initial_phase_graph_ = initial_phase_graph;
}

void Statistics::SaveHeadQuarterQueueSize(unsigned int size) {
    hq_queue_size_ += (double) size;
    countSaveSizeHQ++;
}

void Statistics::SaveDepotQueueSize(unsigned int size, int id_depot) {
    depotQueueSize_[id_depot] += (double)size;
    countSaveDepotQueueSize_[id_depot]++;
}

void Statistics::SaveCargoQueuingTime(double time) {
    time_sum_cargoQueuing_ += time;
    countSaveCargoQueuing++;
}

void Statistics::SaveTransportTime(double time) {
    time_sum_cargoTransport_ += time;
    countSaveCargoTransportTime_++;
}

void Statistics::SaveUtilization(double time, double simulation_time) {
    time_sum_time_of_utilization_ += time;
    if(initial_phase_graph_){
        ofstream outfile;
        outfile.open("Graph.txt", std::ios_base::app);
        // 8 is the number of trucks
        outfile << time << " " << (time_sum_time_of_utilization_ / 8) / time << endl;
        outfile.close();
    }
}

void Statistics::PrintStatistics(double time) {
    ofstream outfile2;
    outfile2.open("Statistics.txt", std::ios_base::app);
    cout << "The average queuing time of a cargo batch: " << time_sum_cargoQueuing_ / countSaveCargoQueuing << endl;
    cout << "The average number of queued cargo units in headquarters: " << hq_queue_size_ / countSaveSizeHQ << endl;
    cout << "Depots: " << endl;
    outfile2 << "********************************Start of New Statistics**********************************" << endl;
    outfile2 << "The average queuing time of a cargo batch: " << time_sum_cargoQueuing_ / countSaveCargoQueuing << endl;
    outfile2 << "The average number of queued cargo units in headquarters: " << hq_queue_size_ / countSaveSizeHQ << endl;
    outfile2 << "Depots: " << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << i << " : " << depotQueueSize_[i] / countSaveDepotQueueSize_[i] << endl;
        outfile2 << i << " : " << depotQueueSize_[i] / countSaveDepotQueueSize_[i] << endl;
    }
    cout << "the average transport time for a cargo batch: " << time_sum_cargoTransport_ / countSaveCargoTransportTime_ << endl;
    cout << "the average utilization of truck: " << (time_sum_time_of_utilization_ / 8) / time << endl;
    outfile2 << "the average transport time for a cargo batch: " << time_sum_cargoTransport_ / countSaveCargoTransportTime_ << endl;
    outfile2 << "the average utilization of truck: " << (time_sum_time_of_utilization_ / 8) / time << endl;
}

void Statistics::ResetStatistics() {
    for (int i = 0; i < 6; i++)
    {
        depotQueueSize_[i] = 0;
        countSaveDepotQueueSize_[i] = 0;
    }
    hq_queue_size_ = 0;
    countSaveSizeHQ = 0;
    time_sum_cargoQueuing_ = 0;
    countSaveCargoQueuing = 0;
    time_sum_time_of_utilization_ = 0;
    time_sum_cargoTransport_ = 0;
    countSaveCargoTransportTime_ = 0;
}
