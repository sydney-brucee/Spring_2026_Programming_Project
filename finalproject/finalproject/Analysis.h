//
//  Analysis.h
//  finalproject
//
//  Created by Sydney on 5/10/26.
//
#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "FirePoint.h"
#include <vector>

class Analysis {
public:
    // Runs all analysis & prints the 6 plots + results
    static void runAnalysis(const std::vector<FirePoint>& fires);

private:
    // Plot 1: Visualizes geographic distribution of fires
    static void plotFireLocations(const std::vector<FirePoint>& fires);
    
    // Plot 2: Shows distribution of fire brightness values
    static void plotBrightnessHistogram(const std::vector<FirePoint>& fires);
    
    // Plot 3: Shows how many fires occurred each day (time series)
    static void plotTimeSeries(const std::vector<FirePoint>& fires);
    
    // Plot 4: Categorizes fires by intensity and spread potential
    static void plotIntensityVsSpread(const std::vector<FirePoint>& fires);
    
    // Plot 5: Groups fires into high-risk vs low-risk with thresholds
    static void plotRiskClustering(const std::vector<FirePoint>& fires);
    
    // Plot 6: Linear regression (Brightness vs FRP)
    static void plotLinearRegression(const std::vector<FirePoint>& fires);
};

#endif
