//
//  Simulation.cpp
//  finalproject
//
//  Created by Sydney on 4/21/26.
//

#include "Simulation.h"
#include "DataLoader.h"
#include <iostream>

void Simulation::loadData(const vector<string>& files) {
    DataLoader loader;
    // Loads all fires from the 14 CSV files & stores them
    fires = loader.loadMultipleFiles(files);
    // Places the real satellite-detected fires onto simulation grid
    grid.seedFire(fires);
}

void Simulation::run(int steps) {
    cout << endl << "=== Fire Simulation Grid ===" << endl;
    // Printing legend for viewer
    cout << "Legend: \033[31mF\033[0m = New Fire | \033[33mF\033[0m = Ongoing Fire | # = Burned | ~ = Water | = = Road | B = Building\n" << endl;
    // Main simulation loop
    for (int i = 0; i < steps; i++) {
        cout << "==== Step " << i << " ====" << endl << endl;
        
        grid.display();         // Shows current state of the grid
        grid.spreadFire();      // Simulates fire spread for each step
        cout << endl << endl;
    }
    // Final summary after simulation ends
    cout << "\n==== SIMULATION COMPLETE ====\n";
    cout << "Total steps: " << steps << endl;
    cout << "Final burning cells: " << grid.countBurning() << endl;
    cout << "Total burned cells: " << grid.countBurned() << endl;
    cout << "Total fires originally loaded: " << fires.size() << endl;
}
