# Wildfire Detection and Spread Analysis (C++)

Final project for a programming course. Processes real satellite-detected wildfire data and explores the relationship between initial fire intensity and spread patterns.

## Dataset
NASA FIRMS MODIS C6.1 active fire detections (contiguous United States). Attributes include latitude, longitude, brightness (intensity), confidence, and timestamps.

## Approach
- Parsed and combined multiple daily CSV files using C++
- Stored fire detections as structured objects
- Mapped detections onto a 2D grid for spatial analysis
- Focused on California detections and explored intensity-based hypotheses about spread

## Hypothesis
Higher initial brightness (intensity) is associated with faster or more extensive simulated spread.

## Planned / Generated Outputs
- Scatter plot of fire locations
- Histogram of brightness values
- Time series of active fires
- Comparison of intensity vs. spread metrics
- Simple clustering of high- and low-risk regions

This project demonstrates data parsing, structured data handling, and basic scientific computing in C++.
