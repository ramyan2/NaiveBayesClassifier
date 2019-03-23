#include "evaluator.h"
#include "data_retriever.h"
#include "image_reader.h"
#include <istream>
#include <sstream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <math.h>  

using namespace std;
Evaluator::Evaluator() {}
//checks accuracy and updates the confusion matrix of a data retriever object  
Evaluator::Evaluator(DataRetriever probability_model) {
    CheckCorrectnessOfModel(std::move(probability_model));
    UpdateConfusionMatrix();
}

//checks accuracy percentage
void Evaluator::CheckCorrectnessOfModel(DataRetriever probability_model) {
    DataRetriever test = DataRetriever("testimages", "testlabels");

    for (int i = 0; i < kNumberOfClasses; i++) {
        for (int j = 0; j < i; j++) {
            confusion_matrix[i][j] = 0;
        }
    }

    int count = 0;
    for (long i = 0; i < test.vector_of_images.size(); i++) {
        int predicted_class = probability_model.CalculatePosteriorProbabilities(test.vector_of_images.at(i));

        if (predicted_class == test.vector_of_labels.at(i)) {
            count++;
        }
        //?
        confusion_matrix[test.vector_of_labels.at(i)][predicted_class]++;
    }

    double number_of_correctly_predicted_classes = (double) (count / test.vector_of_images.size());
    percentage_of_correctly_predicted_classes = number_of_correctly_predicted_classes * 100;

}

//generates a proper confusion matrix
void Evaluator::UpdateConfusionMatrix() {
    for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
        CalculateTotalNumberOfImagesPerClass(confusion_matrix, class_number);
    }
}
//helper for updating the confusion matrix
void Evaluator::CalculateTotalNumberOfImagesPerClass(int matrix[10][10], int row) {
    int number_of_class_images = 0;
        for (int j = 0; j < kNumberOfClasses; j++) {
            number_of_class_images += matrix[row][j];
        }

        for (int k = 0; k < kNumberOfClasses; k++) {
            matrix[row][k] = (matrix[row][k] / number_of_class_images) * 100;
        }
}




