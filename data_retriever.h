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
        int class_of_image;
    public:
        std::vector<double> vector_of_posterior_probabilities;
        double probability_model[28][28][10][2];
        static const int kImageLength = 28;
        static const int kNumberOfClasses = 10;
        DataRetriever();
        void SetToZero(double model[28][28][10][2]);
        void SetLikelihoodToModel(double model[28][28][10][2]);
        void SaveModelToFile(string probability_file);
        bool RetrieveTrainingImages(string file);
        bool RetrieveTrainingLabels(string file);
        double CalculateLikelihoodForEachIndex(int row, int col, int class_number, int feature); 
        double CalculatePriorsProbability(int class_number);
        void CreateProbabilityModel();
        void LoadModelFromFile(string probability_file);
        int CalculatePosteriorProbabilities(ImagesReader image);
        DataRetriever(string training_images_file, string training_labels_file);
        std::vector<double> CreateVectorOfPriorsProbability();
        void SavePriorsModelToFile(string priors_file);
        void LoadPriorsModelFromFile(string priors_file);
        DataRetriever(string type, string stored_training_images_file, string stored_training_priors_file);
};
#endif