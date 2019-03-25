#ifndef CLASSIFY_H
#define CLASSIFY_H

#include "image_reader.h"
#include "data_retriever.h"
#include "classifier.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


class Evaluator { 
    private:
        int confusion_matrix[10][10];
        double percentage_of_correctly_predicted_classes;
    public:
        static const int kImageLength = 28;
        static const int kNumberOfClasses = 10;
        Evaluator();
        Evaluator(Classifier probability_model);


        void CheckCorrectnessOfModel(DataRetriever probability_model); 
        void UpdateConfusionMatrix();
        void CalculateTotalNumberOfImagesPerClass(int matrix[10][10], int row);
        friend ostream &operator<<(ostream &output_stream, const Evaluator &evaluator);
};
#endif