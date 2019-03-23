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


class Evaluator { 
    private:
        double probability_model[28][28][10][2];
        int confusion_matrix[10][10];
        double percentage_of_correctly_predicted_classes;
    public:
        static const int kImageLength = 28;
        static const int kNumberOfClasses = 10;
        Evaluator();
        Evaluator(DataRetriever probability_model);
        void CheckCorrectnessOfModel(DataRetriever probability_model); 
        void UpdateConfusionMatrix();
        void CalculateTotalNumberOfImagesPerClass(int matrix[10][10], int row);
};
#endif