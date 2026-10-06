//
//  main.cpp
//  finalproject
//
//  Created by Sydney on 4/21/26.
//
#include <iostream>
#include "Simulation.h"
#include "Analysis.h"

int main() {
    Simulation sim;

    // List of all 14 data files containing NASA FIRMS wildlife detection data
    vector<string> files = {
        "51.txt", "52.txt", "53.txt", "54.txt", "55.txt", "56.txt", "57.txt", "58.txt", "59.txt", "60.txt", "61.txt", "62.txt", "63.txt", "64.txt"
    };
    
    // load all fire data from CSVs & seed them onto the grid
    sim.loadData(files);
    // run fire spread simulation for 10 steps
    sim.run(10);
    
    cout << "\nRunning data analysis and generating 6 plots...\n";
    // performing data analysis and generating the plots
    Analysis::runAnalysis(sim.getFires());
    
    cout << "\n==== PROJECT COMPLETE ====\n";
    
    return 0;
}

// product -> copy build folder path -> terminal -> cd paste path /Products/Debug -> ./name of program to run
