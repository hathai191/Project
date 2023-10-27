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
    yearlyTempAnalysis.handle_csv();

    
    WeatherDataAnalysis weatherAnalysis(filename);
    weatherAnalysis.readWeatherData();

    std::vector<std::tuple<std::string, int, double>> seasonAverages;

    // Get the list of years from your data
    std::vector<int> years = weatherAnalysis.getYears();

    // Calculate and store average temperatures for each season and each year
    const int startYear = 1780;
    const int endYear = 2023;

    for (int year = startYear; year <= endYear; year++) {
        seasonAverages.push_back(std::make_tuple("Spring", year, weatherAnalysis.calculateAverageSeasonTemperature(3, 5, year)));
        seasonAverages.push_back(std::make_tuple("Summer", year, weatherAnalysis.calculateAverageSeasonTemperature(6, 8, year)));
        seasonAverages.push_back(std::make_tuple("Autumn", year, weatherAnalysis.calculateAverageSeasonTemperature(9, 11, year)));
        seasonAverages.push_back(std::make_tuple("Winter", year, weatherAnalysis.calculateAverageSeasonTemperature(12, 2, year)));

        // Output season averages for each year
        for (const auto& entry : seasonAverages) {
            std::string season;
            int year;
            double averageTemp;
            std::tie(season, year, averageTemp) = entry;

            std::cout << "Season: " << season << ", Year: " << year
                    << ", Average Temperature: " << averageTemp << " °C" << std::endl;
        }
    }
    // Create a histogram or perform further analysis as needed.
    
    return 0;
}

