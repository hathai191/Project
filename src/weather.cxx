#include "weather.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <tuple>

WeatherDataAnalysis::WeatherDataAnalysis(const std::string& cleaneddata_Lund) : filename(cleaneddata_Lund) {
    // Constructor: Initialize the filename
}

void WeatherDataAnalysis::readWeatherData() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the CSV file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string value;
        std::vector<std::string> tokens;

        // Tokenize the line using ';' as the delimiter
        while (std::getline(ss, value, ';')) {
            tokens.push_back(value);
        }

        if (tokens.size() < 3) {
            throw std::runtime_error("Invalid data format in the CSV file.");
        }

        // Assuming the format is: Date, Time, Temperature
        std::string date = tokens[0];
        std::string time = tokens[1];
        double temperature = std::stod(tokens[2]);

        // Extract year, month, and date
        std::istringstream datestream(date);
        std::string yearstr, monthstr, daystr;
        std::getline(datestream, yearstr, '-');
        std::getline(datestream, monthstr, '-');
        std::getline(datestream, daystr, '-');

        // Convert year, month, and date to integers
        int year = std::stoi(yearstr);
        int month = std::stoi(monthstr);
        int day = std::stoi(daystr);

        // Add the date, time, and temperature to the respective vectors
        dates.push_back(date);
        times.push_back(time);
        temperatures.push_back(temperature);
        years.push_back(year);
        months.push_back(month);
        days.push_back(day);
    }

    file.close();
}

double WeatherDataAnalysis::calculateAverageSeasonTemperature(int startMonth, int endMonth, int year) {
    double sum = 0.0;
    int count = 0;

    for (size_t i = 0; i < years.size(); i++) {
        int month = months[i];

        if (years[i] == year && ((startMonth <= endMonth && month >= startMonth && month <= endMonth) ||
            (startMonth > endMonth && (month >= startMonth || month <= endMonth)))) {
            sum += temperatures[i];
            count++;
        }
    }

    if (count > 0) {
        return sum / count;
    } else {
        return 0.0; // No data available for the specified season and year
    }
}

