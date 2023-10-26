#ifndef WEATHER_DATA_ANALYSIS_H
#define WEATHER_DATA_ANALYSIS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

struct TemperatureInfo {
    double temperature;
    std::string date;
    std::string time;
};

class WeatherDataAnalysis {
public:
    WeatherDataAnalysis(const std::string& cleaneddata_Lund);

    void readWeatherData();

    double calculateAverageSpringTemperature(const WeatherDataAnalysis& weatherAnalysis) const;

    const std::vector<int>& getYears() const {
        return years;
    }

    const std::vector<int>& getMonths() const {
        return months;
    }

    const std::vector<int>& getDays() const {
        return days;
    }

    const std::vector<double>& getTemperatures() const {
        return temperatures;
    }

private:
    std::string filename;
    std::vector<std::string> dates;
    std::vector<std::string> times;
    std::vector<double> temperatures;
    std::vector<int> years;
    std::vector<int> months;
    std::vector<int> days;
};

#endif /* WEATHER_DATA_Analysis_H */

