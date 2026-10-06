//
//  Analysis.cpp
//  finalproject
//
//  Created by Sydney on 5/10/26.
//
#include "Analysis.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

void Analysis::runAnalysis(const std::vector<FirePoint>& fires) {
    if (fires.empty()) {
        std::cout << "No fires to analyze!\n";
        return;
    }

    std::cout << "\n=== WILDFIRE DATA ANALYSIS & VISUALIZATION ===\n";
    std::cout << "Total fires detected: " << fires.size() << "\n\n";

    plotFireLocations(fires);           // Plot 1 - Geographic distribution
    plotBrightnessHistogram(fires);     // Plot 2 - Brightness distribution
    plotTimeSeries(fires);              // Plot 3 - Fires per day
    plotIntensityVsSpread(fires);       // Plot 4 - Intensity categories
    plotRiskClustering(fires);          // Plot 5 - Risk clustering
    plotLinearRegression(fires);        // Plot 6 - Linear regression

    std::cout << "=== Data Analysis Complete ===\n\n";
}

// Plot 1: Fire Locations (Text Scatter)
void Analysis::plotFireLocations(const std::vector<FirePoint>& fires) {
    cout << "1) Scatter Plot - Fire Locations (Lat vs Lon)\n";
    cout << "BLANK = 0 fires | . = 1 fire | * = ≤5 fires | # = >5 fires" << endl;
    const int rows = 15, cols = 30;
    int grid[15][30] = {0}; // small grid for counting fire density

    // Map each fire's real coordinates to a small grid cell
    for (const auto& f : fires) {
        int y = static_cast<int>((48.0 - f.lat) * (rows / 33.0));
        int x = static_cast<int>((f.lon + 120.0) * (cols / 65.0));
        if (y >= 0 && y < rows && x >= 0 && x < cols) {
            grid[y][x]++; //  Counting how many fires are in the cell
        }
    }

    // Printing the density map row by row
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            int count = grid[y][x];
            if (count == 0) { cout << " "; }            // Empty area
            else if (count == 1) { cout << "."; }       // 1 fire
            else if (count <= 5) { cout << "*"; }       // 2-5 fires
            else { cout << "#"; }                       // 6+ fires
        }
        cout << "\n";
    }
    cout << "\n";
}

// Plot 2: Histogram of Fire Brightness Values
void Analysis::plotBrightnessHistogram(const std::vector<FirePoint>& fires) {
    std::cout << "2) Histogram of Fire Brightness Values\n";
    int bins[10] = {0};         // 10 bins to count frequency of brightness values
    // Bin each fire's brightness (starting from 290, each bin covers 8 units)
    for (const auto& f : fires) {
        int bin = static_cast<int>((f.brightness - 290) / 8);
        if (bin >= 0 && bin < 10) bins[bin]++;
    }

    // Find the bin with the most fires (used to scale the bar lengths)
    int maxCount = 0;
    for (int i = 0; i < 10; i++) if (bins[i] > maxCount) maxCount = bins[i];

    // Print each bin as a bar chart
    for (int i = 0; i < 10; i++) {
        int start = 290 + i * 8;
        std::cout << std::setw(3) << start << "-" << (start + 7) << ": "
                  << std::string(bins[i] * 30 / (maxCount + 1), '#')
                  << " (" << bins[i] << ")\n";
    }
    std::cout << "\n";
}

// Plot 3: Time Series - Number of Fires per Day
void Analysis::plotTimeSeries(const std::vector<FirePoint>& fires) {
    std::cout << "3) Time Series - Number of Fires per Day\n";
    std::map<std::string, int> daily;       // maps date string ... # of fires on that day
    // count how many fires occurred on each day
    for (const auto& f : fires) {
        daily[f.date]++;  // grouping by date
    }
    
    // print each day with a bar representing the # of fires
    for (const auto& p : daily) {
        std::cout << "   " << p.first << ": "       // printing the date
                  << std::string(p.second / 25 + 1, '#')    // bar
                  << " (" << p.second << " fires)\n";
    }
    std::cout << "\n";
}

// Plot 4: Initial Fire Intensity vs Spread Potential
void Analysis::plotIntensityVsSpread(const std::vector<FirePoint>& fires) {
    std::cout << "4) Initial Fire Intensity vs Spread Potential\n";
    int high = 0, med = 0, low = 0; // counters for intensity categories
    // classify each fire based on brightness and FRP
    for (const auto& f : fires) {
        if (f.brightness > 340 || f.frp > 80) high++;   // high intensity
        else if (f.brightness > 310) med++;     //  medium intensity
        else low++;         // low intensity
    }
    // Dipslaying the results
    std::cout << "   High Intensity (Fast Spread): " << high << "\n";
    std::cout << "   Medium Intensity            : " << med << "\n";
    std::cout << "   Low Intensity               : " << low << "\n\n";
}

// Plot 5: High-Risk vs Low-Risk Fire Clustering
void Analysis::plotRiskClustering(const std::vector<FirePoint>& fires) {
    std::cout << "5) High-Risk vs Low-Risk Fire Clustering\n";
    int highRisk = 0; // counter for high-risk fires
    // threshold-based clustering
    for (const auto& f : fires) {
        // A fire is considered high-risk if it has high brightness or FRP
        if (f.brightness >= 330 || f.frp >= 50) highRisk++;
    }
    // display results with percentage
    std::cout << "    High-Risk Fires  : " << highRisk
              << " (" << (highRisk * 100.0 / fires.size()) << "%)\n";
    std::cout << "    Low-Risk Fires   : " << (fires.size() - highRisk) << "\n\n";
}

// 6. Linear Regression - Brightness vs FRP
void Analysis::plotLinearRegression(const std::vector<FirePoint>& fires) {
    std::cout << "6) Linear Regression - Brightness vs FRP\n";

    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    size_t n = fires.size(); // number of data points

    // calculating the sums needed for linear regression
    for (const auto& f : fires) {
        double x = f.brightness; // independent
        double y = f.frp;        // dependent
        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
    }

    // calculate slope (m) and intercept (b)
    double m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);     // slope
    double b = (sumY - m * sumX) / n;                                     // intercept

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "   Regression Equation: FRP = " << m << " * Brightness + " << b << "\n";

    // interpret strength of the relationship
    std::cout << "   Correlation Strength: ";
    if (std::abs(m) > 1.5)      std::cout << "Strong positive relationship\n";
    else if (std::abs(m) > 0.8) std::cout << "Moderate positive relationship\n";
    else                        std::cout << "Weak relationship\n";

    // Visualization of regression line
    std::cout << "\n   Visualization (Brightness -> Predicted FRP):\n";
    for (int i = 290; i <= 400; i += 20) {
        double predicted = m * i + b;
        int barLength = static_cast<int>(predicted / 8.0);
        if (barLength < 0) barLength = 0; // prevents a negative bar length
        
        std::cout << "   " << std::setw(3) << i
                  << " brightness → predicted FRP: "
                  << std::setw(7) << predicted
                  << "   " << std::string(barLength, '#') << "\n";
    }
    std::cout << "\n";
}
