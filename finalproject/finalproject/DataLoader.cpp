//
//  DataLoader.cpp
//  finalproject
//
//  Created by Sydney on 4/21/26.
//

#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

FirePoint DataLoader::parseLine(const string& line) {
    FirePoint f = {0.0, 0.0, 0.0, 0.0, ""};
    stringstream ss(line);
    string token;
    vector<string> tokens;
    
    // col order: 0 lat, 1 lon, 2 bright, 11 frp
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() < 12) { return f; } // invalid line
    
    try {
        f.lat = stod(tokens[0]);
        f.lon = stod(tokens[1]);
        f.brightness = stod(tokens[2]);
        f.frp = stod(tokens[11]);
        f.date = tokens[5];
    } catch (...) {
        // skipping bad lines here
    }
    
    return f;
}

vector<FirePoint> DataLoader::loadFile(const string& filename) {
    vector<FirePoint> data;
    ifstream ifile(filename);
    
    if (!ifile.is_open()) {
        cout << "Error opening file: " << filename << endl << "Please try again!" << endl;
        return data;
    }
    string line;
    getline(ifile, line); // skipping header
    
    int count = 0;
    while (getline(ifile, line)) {
        if (!line.empty()) {
            FirePoint fp = parseLine(line);
            // adding if coords valid
            if (fp.lat != 0.0 || fp.lon != 0.0) {
                data.push_back(fp);
                count++;
            }
        }
    }
    cout << "Parsed " << count << " valid fires." << endl;
    return data;
}

vector<FirePoint> DataLoader::loadMultipleFiles(const vector<string>& files) {
    vector<FirePoint> allData;
    
    for (const string& file : files) {
        vector<FirePoint> temp = loadFile(file);
        allData.insert(allData.end(), temp.begin(), temp.end());
        cout << "Loaded " << temp.size() << " fires from " << file << endl;
    }
    cout << "Total fires loaded: " << allData.size() << endl;
    
    return allData;
}
