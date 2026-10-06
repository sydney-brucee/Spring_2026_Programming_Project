//
//  FirePoint.h
//  finalproject
//
//  Created by Sydney on 4/21/26.
//

#ifndef FIREPOINT_H
#define FIREPOINT_H

#include <string>
using namespace std;

struct FirePoint {
    double lat;             // Latitude
    double lon;             // Longitude
    double brightness;      // Brightness temperature
    double frp;             // Fire Radiative Power (FRP)
    string date;            // Acquisition date
};

#endif
