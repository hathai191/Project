#include <TGraph.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <fstream>
#include <vector>

// Function to create a TGraph and add it to a TMultiGraph
void createGraph(const char* filename, TMultiGraph* multiGraph, const char* title, Color_t color) {
    // Read data from the CSV file
    std::vector<Double_t> years;
    std::vector<Double_t> temperatures;

    ifstream file(filename);

    Double_t year;
    Double_t temperature;

    while (file >> year >> temperature) {
        years.push_back(year);
        temperatures.push_back(temperature);
    }

    // Create a TGraph with the data
    TGraph* graph = new TGraph(years.size(), years.data(), temperatures.data());
    graph->SetLineColor(color);
    graph->SetTitle(title);
    multiGraph->Add(graph, "l");
}

void draw_seasonal_averages() {
    // Load the data from the CSV files into TGraphs
    TMultiGraph* multiGraph = new TMultiGraph();
    multiGraph->SetTitle("Seasonal Averages");

    createGraph("spring.csv", multiGraph, "Spring", kRed);
    createGraph("summer.csv", multiGraph, "Summer", kBlue);
    createGraph("autumn.csv", multiGraph, "Autumn", kGreen);
    createGraph("winter.csv", multiGraph, "Winter", kOrange);

    // Create a TCanvas for drawing
    TCanvas* canvas = new TCanvas("Seasonal Averages", "Seasonal Averages", 800, 600);

    // Set the axis labels
    multiGraph->GetXaxis()->SetTitle("Year");
    multiGraph->GetYaxis()->SetTitle("Average Temperature (°C)");

    // Draw the multiGraph with "APL" to add points, show the legend, and draw the axis
    multiGraph->Draw("APL");

    // Create a legend to label the lines
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(multiGraph->GetListOfGraphs()->At(0), "Spring", "l");
    legend->AddEntry(multiGraph->GetListOfGraphs()->At(1), "Summer", "l");
    legend->AddEntry(multiGraph->GetListOfGraphs()->At(2), "Autumn", "l");
    legend->AddEntry(multiGraph->GetListOfGraphs()->At(3), "Winter", "l");
    legend->Draw();

    // Save the graph as an image
    canvas->Print("seasonal_averages.png");
}
