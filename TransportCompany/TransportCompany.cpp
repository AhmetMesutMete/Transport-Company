#include <iostream>
using namespace std;
#include "Simulations.h"
int main() {
    double max_time; //max_time
    cout << "Please indicate the length of the simulation time: "; cin >> max_time;  cout << endl;

    double initial_phase;
    cout << "Please indicate the duration of the initial time: "; cin >> initial_phase; cout << endl;

    bool custom_cargo;
    cout << "Do you want to use time specified by you to generate cargo? (1 = yes, 0 = no): ";
    cin >> custom_cargo; cout << endl;
    double custom_cargo_hq = -1;
    double custom_cargo_depot = -1;

    if (custom_cargo){ //If custom cargo == 1 take some
        cout << "Please indicate how often the load is going to be generated in HQ: ";
        cin >> custom_cargo_hq;
        cout << endl;
        cout << "Please indicate how often the load is going to be generated in Regional Depots: ";
        cin >> custom_cargo_depot;
        cout << endl;
    }

    bool initial_phase_graph;
    cout << "Do you want to generate an initial phase graph? (1 = yes, 0 = no): ";
    cin >> initial_phase_graph; cout << endl;

    int num_of_simulations;
    cout << "Please indicate the number of simulations you'd like to execute: ";
    cin >> num_of_simulations; cout << endl;

    SeedGen* seed_generator = new SeedGen(992838);
    vector<int> seeds_for_simulations = seed_generator->GenSeeds(num_of_simulations);
    vector<int> seeds_for_one_simulation;

    for (int i = 0; i < num_of_simulations; i++){
        cout << "Simulation " << i+1 << " starts...." << endl;
        //Seeds must be cleared each time
        seeds_for_one_simulation.clear();
        for (int i = 0; i < 8; i++){
            //sending the first seed from seeds vector
            seeds_for_one_simulation.push_back(seeds_for_simulations[0]);
            //After cleaning the seed we took we can take another one
            seeds_for_simulations.erase(seeds_for_simulations.begin());
        }
        Simulations* simulation = new Simulations(
                initial_phase,
                max_time,
                custom_cargo,
                custom_cargo_hq,
                custom_cargo_depot,
                seeds_for_one_simulation,
                initial_phase_graph);

        simulation->Start();
        delete simulation;
    }
    return 0;
}
