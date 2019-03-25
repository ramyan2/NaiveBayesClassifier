#ifndef DATA_H
#define DATA_H

#include "image_reader.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class DataRetriever { 
    private:
            double k_value = 0.1;
    public:
    DataRetriever();
    DataRetriever(string training_images_file, string training_labels_file);

    bool RetrieveTrainingImages(string file);
    bool RetrieveTrainingLabels(string file);
    double CalculateLikelihoodForEachIndex(int row, int col, int class_number, int feature); 
    double CalculatePriorsProbability(int class_number);
    std::vector<double> CreateVectorOfPriorsProbability();

        std::vector<ImagesReader> vector_of_images;
        std::vector<int> vector_of_labels;
        std::vector<double> vector_of_posterior_probabilities;
        double probability_model[28][28][10][2];
        static const int kImageLength = 28;
        static const int kNumberOfClasses = 10;
  
};
#endif