Use this folder to develop your project.

Dataset: https://nrt3.modaps.eosdis.nasa.gov/archive/FIRMS/modis-c6.1/USA_contiguous_and_Hawaii/ 
    Files: 2026051-2026064

Briefly describe the dataset you’re going to use

I will be using 14 days of wildfire detection data from NASA FIRMS (Fire Information for Resource Management System), specifically the MODIS C6.1 dataset for the contiguous United States. The dataset contains satellite-detected active fire locations with attributes such as latitude, longitude, brightness (fire intensity), confidence level, and timestamps


Briefly describe the hypothesis you plan on testing

I hypothesize that wildfire detections with higher initial intensity (brightness) are associated with faster and more extensive spread patterns in the simulation.


Briefly describe the data processing technique(s) you plan on using

The raw CSV (turned .txt) files will be parsed using fstream and sstream and combined into a single dataset. Each fire detection will be stored as a structured object with geographic coords, intensity, and time information. Latitude and longitude values will be mapped onto a 2D grid to create a simulation space. The dataset will (probably) be filtered to focus on California, and values such as brightness may be normalized for use in probabilistic fire spread calculations.


Briefly describe the plots/visualizations you plan on generating

Five plots will be generated to explore and analyze the data:
    1) Scatter plot of fire locations across the map
    2) Histogram of fire brightness values
    3) Time series plot showing number of active fires per day
    4) Comparing initial fire intensity to simulated spread rate
    5) Clustering visualization grouping fire detections into high and low-risk regions.
These plots will help me visualize the relationship between fire intensity and spread behavior.
