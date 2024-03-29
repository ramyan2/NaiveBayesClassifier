#ifndef CLASSIFY_H
#define CLASSIFY_H

#include "image_reader.h"
#include "data_retriever.h"
#include "classifier.h"
#include "data_retriever.h"
#include "image_reader.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


class Evaluator { 
    public:
        double confusion_matrix[10][10];
        double percentage_of_correctly_predicted_classes;
        static const int kImageLength = 28;
        static const int kNumberOfClasses = 10;
        Evaluator();
        Evaluator(Classifier probability_model);
        void CheckCorrectnessOfModel(Classifier probability_model);
        void CalculateTotalNumberOfImagesPerClass(double matrix[10][10], int row);
        friend ostream &operator<<(ostream &output_stream, const Evaluator &evaluator);
};
#endif