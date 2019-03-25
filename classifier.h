#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include "data_retriever.h"

using namespace std;


class Classifier { 
    public:
    double probability_model[28][28][10][2];
    std::vector<double> priors_vector;
    static const int kImageLength = 28;
    static const int kNumberOfClasses = 10;
    Classifier();
    Classifier(string images_data_file, string labels_data_file);
    void SetToZero();
    void SetLikelihoodToModel(DataRetriever training_model);    
    void CreateProbabilityModel(DataRetriever training_model);
    void CreatePriorsModel(DataRetriever training_model);
    int CalculatePosteriorProbabilities(ImagesReader image);
    void LoadModelFromFile(string probability_file);
    void LoadPriorsModelFromFile(string priors_file);
    void SaveModelToFile(string probability_file);
    void SavePriorsModelToFile(string priors_file);
};
#endif