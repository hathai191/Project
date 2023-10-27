#include "include/weather.h"
#include "include/year_temp_anlys.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <tuple>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <CSV filename>" << std::endl;
        return 1;
    }

    const std::string filename = argv[1];

    YearlyTempAnalysis yearlyTempAnalysis(filename);
    const int year = 2021;
    yearlyTempAnalysis.handle_csv(year);

    
    WeatherDataAnalysis weatherAnalysis(filename);
    weatherAnalysis.readWeatherData();

    // Calculate and store average temperatures for each season and each year
    const int startYear = 1780;
    const int endYear = 2022;

    std::vector<std::tuple<int, double>> springData, summerData, autumnData, winterData;

    for (int year = startYear; year <= endYear; year++) {
        springData.push_back(std::make_tuple(year, weatherAnalysis.calculateAverageSeasonTemperature(3, 5, year)));
        summerData.push_back(std::make_tuple(year, weatherAnalysis.calculateAverageSeasonTemperature(6, 8, year)));
        autumnData.push_back(std::make_tuple(year, weatherAnalysis.calculateAverageSeasonTemperature(9, 11, year)));
        winterData.push_back(std::make_tuple(year, weatherAnalysis.calculateAverageSeasonTemperature(12, 2, year)));
    }

    // Save the data to separate CSV files for each season
    std::ofstream springFile("spring.csv");
    std::ofstream summerFile("summer.csv");
    std::ofstream autumnFile("autumn.csv");
    std::ofstream winterFile("winter.csv");

    if (!springFile.is_open() || !summerFile.is_open() || !autumnFile.is_open() || !winterFile.is_open()) {
        std::cerr << "Failed to open one or more output files for writing." << std::endl;
        return 1;
    }

    for (const auto& entry : springData) {
        int year;
        double averageTemp;
        std::tie(year, averageTemp) = entry;
        springFile << year << " " << averageTemp << std::endl;
    }

    for (const auto& entry : summerData) {
        int year;
        double averageTemp;
        std::tie(year, averageTemp) = entry;
        summerFile << year << " " << averageTemp << std::endl;
    }

    for (const auto& entry : autumnData) {
        int year;
        double averageTemp;
        std::tie(year, averageTemp) = entry;
        autumnFile << year << " " << averageTemp << std::endl;
    }

    for (const auto& entry : winterData) {
        int year;
        double averageTemp;
        std::tie(year, averageTemp) = entry;
        winterFile << year << " " << averageTemp << std::endl;
    }

    springFile.close();
    summerFile.close();
    autumnFile.close();
    winterFile.close();

    return 0;
}

