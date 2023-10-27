#ifndef YEAR_TEMPERATURE_ANALYSIS_H
#define YEAR_TEMPERATURE_ANALYSIS_H


#include <fstream>
#include <iostream>
#include <vector>

class YearlyTempAnalysis {
public:
    YearlyTempAnalysis(const std::string& cleaneddata_Lulea);

    void generateGraph();
};


#endif /* YEAR_TEMPERATURE_ANALYSIS_H */
