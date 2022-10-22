//
// Created by User on 17.02.2022.
//

#pragma once
#include <vector>
class SeedGen {
private:
    int start_;
    const double kM = 2147483647.0;
    static const int kA = 16807;
    static const int kQ = 127773;
    static const int kR = 2836;
    std::vector<int> seeds_;
public:
    SeedGen(int start_);
    ~SeedGen() = default;
    std::vector<int> GenSeeds(int number_of_simulations);
};
