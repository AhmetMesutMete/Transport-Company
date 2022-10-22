//
// Created by User on 17.02.2022.
//

#include "SeedGen.h"

SeedGen::SeedGen(int start){
    start_ = start;
}

std::vector<int> SeedGen::GenSeeds(int number_of_simulations){
    int counter = 0;
    for (int i = 0; i < 8 * number_of_simulations * 100000; i++){
        counter++;
        // normal generator
        int h = start_ / kQ;
        start_ = kA * (start_ - kQ * h) - kR * h;
        // ****** I realized that there is a problem in the line below and fixed it two lines below
        // start_ = (start_ < 0) ? start_ = start_ + static_cast<int>(kM) : start_;
        start_ = (start_ < 0) ? start_ + static_cast<int>(kM) : start_;
        if (counter >= 100000){
            // push the start_ value to the back side of the seeds vector
            seeds_.push_back(start_);
            counter = 0;
        }
    }
    return seeds_;
}
