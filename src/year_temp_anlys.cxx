#include "year_temp_anlys.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <sstream>
#include <ctime>


YearlyTempAnalysis::YearlyTempAnalysis(const std::string& cleaneddata_Lulea) : filename(cleaneddata_Lulea) {
    // Constructor
    std::ifstream file(filename);
    // load CSV values into variables
}

void YearlyTempAnalysis::handle_csv() {
    // find year

    // transform date to number


    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open CSV file" << std::endl;
    }


    std::string date, temp;
    std::string data, line;

    while (std::getline(file, line)) {
        std::istringstream s(line);
        std::vector<std::string> tokens;

        while (std::getline(s, data, ';')) {
            tokens.push_back(data);
        }

        date = tokens[0];
        temp = tokens[1];

        // read the date and temperature
        std::tm t = {};
        strptime(date.c_str(), "%Y-%m-%d", &t);
        if (t.tm_year % 4 == 0 && t.tm_yday > 58) {
            if (t.tm_yday == 59) {

            } else {
                days[t.tm_yday-1].push_back(temp);
            }
        } else {
            days[t.tm_yday].push_back(temp);
        }
    }
}