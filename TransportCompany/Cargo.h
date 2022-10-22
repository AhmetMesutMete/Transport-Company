//
// Created by User on 17.02.2022.
//
#pragma once
class Cargo {
private:
    int id_;
    double size_;
    double gen_time_;
public:
    Cargo(int id, double size, double gen_time);
    int GetId();
    double GetSize();
    double GetTimeQueueing(double time);
    double GetTimeTransport(double time);
};
