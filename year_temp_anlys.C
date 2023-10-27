#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TAxis.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <numeric> 

void PlotTemperatureWithErrors(const std::vector<double>& temperatures, const std::vector<double>& standardDeviations) {
    auto c1 = new TCanvas("c1", "A graph of the yearly daily temperature with error bars", 200, 30, 800, 400);

    const Int_t n = 365;
    Double_t x[n];
    std::iota(x, x + n, 1); // Fill x with values from 1 to 365
    Double_t y[n];
    Double_t ex[n] = {0};
    Double_t ey[n];

    for (int i = 0; i < n; i++) {
        y[i] = temperatures[i];
        ey[i] = standardDeviations[i];
    }

    auto gr = new TGraphErrors(n, x, y, ex, ey);
    gr->SetTitle("");
    gr->SetMarkerColor(3);
    gr->Draw("AP");

    c1->SaveAs("yearly_plot.png");
}

int main() {
    std::vector<double> temperatures;
    std::vector<double> standardDeviations;

    std::ifstream file("temperature_analysis.csv");

    double temperature;
    double standard_deviation;

    while (file >> temperature >> standard_deviation) {
        temperatures.push_back(temperature);
        standardDeviations.push_back(standard_deviation);
    }
    PlotTemperatureWithErrors(temperatures, standardDeviations);

    return 0;
}