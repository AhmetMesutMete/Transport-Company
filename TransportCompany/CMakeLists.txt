cmake_minimum_required(VERSION 3.21)
project(TransportCompany)

set(CMAKE_CXX_STANDARD 14)

add_executable(TransportCompany TransportCompany.cpp Truck.cpp Truck.h HQ.cpp HQ.h Depot.cpp Depot.h SeedGen.cpp SeedGen.h Simulations.cpp Simulations.h Cargo.cpp Cargo.h Statistics.cpp Statistics.h)
