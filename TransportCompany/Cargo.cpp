//
// Created by User on 17.02.2022.
//
#include "Cargo.h"
Cargo::Cargo(int id, double size, double gen_time) {
    size_ = (size < 0) ? 0.1 : ((size > 10) ? 10 : size);
    id_ = id;
    gen_time_ = gen_time;
}

// Get the ID of the Cargo Batch
int Cargo::GetId() {
    return id_;
}

// Get the size of the Cargo Batch
double Cargo::GetSize() {
    return size_;
}

// How long was the Cargo Batch has been in the queue after generation time
double Cargo::GetTimeQueueing(double time) {
    return time - gen_time_;
}

//Get the Transportation Time of a certain Cargo Batch
double Cargo::GetTimeTransport(double time) {
    return time - gen_time_;
}