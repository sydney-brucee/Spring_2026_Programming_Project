//
//  Simulation.h
//  finalproject
//
//  Created by Sydney on 4/21/26.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>
#include "FirePoint.h"
#include "Grid.h"

using namespace std;

class Simulation {
private:
    vector<FirePoint> fires;
    Grid grid;
    
public:
    // Loads wildfire data from multple CSV files using DataLoader class & seeds fires onto the grid
    void loadData(const vector<string>& files);
    // Runs the fire spread simulation for 10 steps & prints each step
    void run(int steps);
    // Returns a const reference to the loaded FirePoint objects so Analysis class can use the data
    const vector<FirePoint>& getFires() const { return fires; }
};

#endif
