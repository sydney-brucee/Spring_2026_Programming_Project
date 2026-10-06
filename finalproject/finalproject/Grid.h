//
//  Grid.h
//  finalproject
//
//  Created by Sydney on 4/21/26.
//

#ifndef GRID_H
#define GRID_H

#include <vector>
#include "FirePoint.h"

using namespace std;

enum CellType {
    EMPTY,      // Normal land
    FIRE,       // Currently burning
    BURNED,     // Previously burned
    WATER,      // Blocks fire
    ROAD,       // Road...Slows fire spread
    BUILDING    // Building...Increases fire spread
};

struct Cell {
    CellType type;
    double intensity;       // Strength of the fire
    bool isNew = false;     // Used to distinguish new fires for visualization
};

class Grid {
private:
    static const int WIDTH = 150;   // Grid width...can adjust
    static const int HEIGHT = 150;  // Grid height...can adjust
    
    Cell cells[HEIGHT][WIDTH];      // 2D array
    // Helper functions to convert real-world coordinates to grid indices
    int mapX(double lon);
    int mapY(double lat);
    
public:
    Grid(); // Constructor
    
    void seedFire(const vector<FirePoint>& fires);      // Places real fires on grid
    void spreadFire();                                  // Simulates one step of fire spread
    void display();                                     // Prints the current state of the grid
    
    int countBurning() const;       // Returns number of cells currently on fire
    int countBurned() const;        // Returns number of burned cells
};

#endif
