#ifndef YEAR_TEMPERATURE_ANALYSIS_H
#define YEAR_TEMPERATURE_ANALYSIS_H



#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


class YearlyTempAnalysis {
public:
    YearlyTempAnalysis(const std::string& cleaneddata_Lulea);

    void handle_csv(const int year);
    double computeStandardDeviation(std::vector<double> data);

private:
    std::string filename;
    double temperature_data[365];
    std::vector<double> days[365];
};


#endif /* YEAR_TEMPERATURE_ANALYSIS_H */
