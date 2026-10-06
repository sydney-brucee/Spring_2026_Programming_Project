//
//  DataLoader.h
//  finalproject
//
//  Created by Sydney on 4/21/26.
//

#ifndef DATALOADER_H
#define DATALOADER_H

#include <vector>
#include<string>
#include "FirePoint.h"

using namespace std;

class DataLoader {
public:
    // Loads a single CSV file and returns all fire points from it
    vector<FirePoint> loadFile(const string& filename);
    // Loads multiple CSV files and combines all fire points into one vector
    vector<FirePoint> loadMultipleFiles(const vector<string>& files);
    
private:
    // Parses one line of the CSV into the FirePoint struct...helper function
    FirePoint parseLine(const string& line);
};

#endif
