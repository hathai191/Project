#include "year_temp_anlys.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <sstream>
#include <ctime>
#include <math.h>


YearlyTempAnalysis::YearlyTempAnalysis(const std::string& cleaneddata_Lulea) : filename(cleaneddata_Lulea) {
    // Constructor
}

void YearlyTempAnalysis::handle_csv(const int year) {

    // Prepare and open file to read from
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open CSV file" << std::endl;
    }


    std::string date;
    double temp;
    std::string data, line;

    std::cout << "[Year_temp_anlys] Begin parsing temperature data" << std::endl; 
    while (std::getline(file, line)) {
        std::istringstream s(line);
        std::vector<std::string> tokens;

        // Tokenizes the line data, splitting the CSV into it's parts
        while (std::getline(s, data, ';')) {
            tokens.push_back(data);
        }

        // We assume we know the format and parse the tokens into our vars
        date = tokens[0];
        temp = std::stod(tokens[1]);

        // Transform our date into a tm struct to get the tm_yday property
        // This lets us index our days properply even if the input data is pruned slightly.
        std::tm t = {};
        strptime(date.c_str(), "%Y-%m-%d", &t);
        // Since the tm struct counts years from 1900 we do this to
        // decide what year we want to plot
        if (t.tm_year == year-1900) {
            temperature_data[t.tm_yday] = temp;
        }
        // Checks for leap years, and if applicable subtract a day so our indexes are proper
        // (and so that we don't go out of bounds on our array)
        if (t.tm_year % 4 == 0 && t.tm_yday > 58) {
            if (! (t.tm_yday == 59)) {
                days[t.tm_yday-1].push_back(temp);
            }
        } else {
            // No leap days here, we carry on
            days[t.tm_yday].push_back(temp);
        }
    }
    std::cout << "[Year_temp_anlys] Parsing of temperature data finished" << std::endl;

    // Here we write our temperature data and standard derivation to a file so that it can be used with ROOT.
    std::ofstream output("temperature_analysis.csv");
    int i = 0;
    for (auto & temperatures : days) {
        
        output << std::to_string(temperature_data[i]) << " " << std::to_string(computeStandardDeviation(temperatures)) << std::endl;
        i+=1;
    }
    std::cout << "[Year_temp_anlys] Output of temperature data complete, module finished" << std::endl;
}

double YearlyTempAnalysis::computeStandardDeviation(std::vector<double> data) {
    // Just a regular standard deviation with a sample since we don't have all possible weather data
    double sum = 0.0;
    for (auto & temperature : data) {
        sum += temperature;
    }
    double median = sum/data.size();

    sum = 0;
    for (auto & temperature : data) {
        sum += (temperature - median) * (temperature - median);
    }
    return sqrt(sum / (data.size()-1));
}