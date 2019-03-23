#ifndef CLASSIFY_H
#define CLASSIFY_H

#include "image_reader.h"
#include "data_retriever.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Classifier { 
    private:
        double probability_model[28][28][10][2];
        
    public:
    static const int kImageLength = 28;
        static const int kNumberOfClasses = 10;
        Classifier();
        void LoadModelFromFile(string probability_file);
        int CalculatePosteriorProbabilities(ImagesReader image);
};
#endif