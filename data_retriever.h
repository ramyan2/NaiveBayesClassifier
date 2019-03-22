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
        std::vector<ImagesReader> vector_of_images;
        std::vector<int> vector_of_labels;
        const int smoothing_factor = 0.1;
        double probability_model[28][28][10][2];
    public:
        static const int kImageLength = 28;
        static const int kNumberOfClasses = 10;
        DataRetriever();
        void SetToZero(double model[28][28][10][2]);
        void SetLikelihoodToModel(double model[28][28][10][2]);
        bool RetrieveTrainingImages(string file);
        bool RetrieveTrainingLabels(string file);
        double CalculateLikelihoodForEachIndex(int row, int col, int class_number, int feature); 
        double CalculatePriorsProbability(int class_number);
        void CreateProbabilityModel();
};
#endif