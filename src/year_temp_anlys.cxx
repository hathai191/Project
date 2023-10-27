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
    // find year

    // transform date to number


    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open CSV file" << std::endl;
    }


    std::string date;
    double temp;
    std::string data, line;

    while (std::getline(file, line)) {
        std::istringstream s(line);
        std::vector<std::string> tokens;

        while (std::getline(s, data, ';')) {
            tokens.push_back(data);
        }

        date = tokens[0];
        temp = std::stod(tokens[1]);

        // read the date and temperature
        std::tm t = {};
        strptime(date.c_str(), "%Y-%m-%d", &t);
        if (t.tm_year == year-1900) {
            temperature_data[t.tm_yday] = temp;
        }

        if (t.tm_year % 4 == 0 && t.tm_yday > 58) {
            if (t.tm_yday == 59) {

            } else {
                days[t.tm_yday-1].push_back(temp);
            }
        } else {
            days[t.tm_yday].push_back(temp);
        }
    }

    std::ofstream output("temperature_analysis.csv");
    int i = 0;
    for (auto & temperatures : days) {
        
        output << std::to_string(temperature_data[i]) << " " << std::to_string(computeStandardDeviation(temperatures)) << std::endl;
        i+=1;
    }
}

double YearlyTempAnalysis::computeStandardDeviation(std::vector<double> data) {
    
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