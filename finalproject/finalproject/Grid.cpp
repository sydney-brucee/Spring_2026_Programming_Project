//
//  Grid.cpp
//  finalproject
//
//  Created by Sydney on 4/21/26.
//

#include "Grid.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

// Constructor...initializes random terrain
Grid::Grid() {
    srand(static_cast<unsigned int>(time(nullptr))); // random seed
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int r = rand() % 100;
            
            if (r < 8) {
                cells[y][x].type = WATER;       // ~8% water (fire blocker)
            } else if (r < 18) {
                cells[y][x].type = ROAD;        // ~10% roads (slows fire)
            } else if (r < 25) {
                cells[y][x].type = BUILDING;    // ~7% buildings (burns faster)
            } else {
                cells[y][x].type = EMPTY;       // ~75% normal land
            }
            cells[y][x].intensity = 0;
        }
    }
}

int Grid::mapX(double lon) {
    return static_cast<int>((lon + 115.0)) * (WIDTH / 50.0);
}

int Grid::mapY(double lat) {
    return static_cast<int>((46.0 - lat) * (HEIGHT / 29.0));
}

void Grid::seedFire(const vector<FirePoint>& fires) {
    int placed = 0;
    for (const auto& f : fires) {
        int x = mapX(f.lon);
        int y = mapY(f.lat);
        
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            cells[y][x].type = FIRE;
            cells[y][x].intensity = f.brightness;
            cells[y][x].isNew = true;
            placed++;
        }
    }
    cout << "Successfully placed " << placed << " fires on the grid!" << endl;
}

void Grid::spreadFire() {
    Cell newGrid[HEIGHT][WIDTH];
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            newGrid[y][x] = cells[y][x]; // copy everything
            newGrid[y][x].isNew = false; // reset new flag
        }
    }
    
    for (int y = 1; y < HEIGHT - 1; y++) {
        for (int x = 1; x < WIDTH - 1; x++) {
            if (cells[y][x].type == FIRE && !cells[y][x].isNew) {
                double intensity = cells[y][x].intensity;
                                    
                auto trySpread = [&](int ny, int nx) {
                    if (cells[ny][nx].type == WATER ||
                        cells[ny][nx].type == FIRE ||
                        cells[ny][nx].type == BURNED) { return; }
                    double chance = intensity;
                        
                    if (cells[ny][nx].type == ROAD) { chance *= 0.25; } // 25% of normal chance
                    if (cells[ny][nx].type == BUILDING) { chance *= 1.6; } // 160% of normal chance
                        
                    double prob = chance / 800.0; // anything 800 brightness & above means 100% spread chance
                    if (prob > 1) { prob = 1; }
                        
                    if ((rand() / (double)RAND_MAX) < prob ) {
                        newGrid[ny][nx].type = FIRE;
                        newGrid[ny][nx].intensity = intensity;
                        newGrid[ny][nx].isNew = true;
                    }
                };
                trySpread(y+1, x);
                trySpread(y-1, x);
                trySpread(y, x+1);
                trySpread(y, x-1);
                    
                // only burn out sometimes, not always!
                double burnOutChance = 0.35; // the higher this is the faster it will burn out
                if ((rand() / (double)RAND_MAX) < burnOutChance) {
                    newGrid[y][x].type = BURNED;
                    // newGrid[y][x].isNew = false;
                }
            }
        }
    }
    // copying back
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            cells[y][x] = newGrid[y][x];
        }
    }
}

void Grid::display() {
    #ifdef _WIN32
        system("color");
    #endif
    for (int y = 0; y < HEIGHT; y++) {
        cout << "|";
        for (int x = 0; x < WIDTH; x++) {
            const Cell& c = cells[y][x];
            char ch = '.';
            switch (c.type) {
                case FIRE: ch = 'F'; break;
                case BURNED: ch = '#'; break;
                case WATER: ch = '~'; break;
                case ROAD: ch = '='; break;
                case BUILDING: ch = 'B'; break;
                default: ch = '.'; break;
            }
            if (c.type == FIRE) {
                if (c.isNew) {
                    cout << "\033[31mF\033[0m"; // Red F = new fire
                } else {
                    cout << "\033[33mF\033[0m"; // existing fires = yellow F
                }
            } else {
                cout << ch; // normal for everything else
            }
        }
        cout << "|" << endl;
    }
    cout << "Burning: " << countBurning() << " | Burned: " << countBurned() << endl;
}

int Grid::countBurning() const {
    int count = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (cells[y][x].type == FIRE) {
                count++;
            }
        }
    }
    return count;
}

int Grid::countBurned() const {
    int count = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (cells[y][x].type == BURNED) {
                count++;
            }
        }
    }
    return count;
}
