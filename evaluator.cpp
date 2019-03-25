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
#include <iomanip>

using namespace std;
Evaluator::Evaluator() {}
//checks accuracy and updates the confusion matrix of a data retriever object  
Evaluator::Evaluator(Classifier probability_model) {
    //calculate accuracy percentage
    //calculate confusion matrix
}

//checks accuracy percentage
void Evaluator::CheckCorrectnessOfModel(DataRetriever probability_model) {
    cout << "Check1";
    probability_model = DataRetriever("testimages", "testlabels");
    for (int i = 0; i < kNumberOfClasses; i++) {
        for (int j = 0; j < 10; j++) {
            confusion_matrix[i][j] = 0;
        }
    }

    // cout << "Initial confusion matrix:";
    // for (int i = 0; i < kNumberOfClasses; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         cout << confusion_matrix[i][j];
    //     }
    //     cout <<'\n';
    // }



    int count = 0;

    cout << "size of vector of images" << probability_model.vector_of_images.size(); 

    for (unsigned long long i = 0; i < probability_model.vector_of_images.size(); i++) {
        int predicted_class = probability_model.CalculatePosteriorProbabilities(probability_model.vector_of_images.at(i));

        if (predicted_class == probability_model.vector_of_labels.at(i)) {
            cout << "matches!";
            count++;
        }
        //?
        confusion_matrix[probability_model.vector_of_labels.at(i)][predicted_class]++;
    }
        cout << "Second confusion matrix:";
    for (int i = 0; i < kNumberOfClasses; i++) {
        for (int j = 0; j < 10; j++) {
            cout << confusion_matrix[i][j];
        }
        cout <<'\n';
    }
    cout << "check 3" << count;
    double number_of_correctly_predicted_classes = (double) (count / probability_model.vector_of_images.size());
    percentage_of_correctly_predicted_classes = number_of_correctly_predicted_classes * 100;
    cout << "amoutn" << percentage_of_correctly_predicted_classes;

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


//ostream 

ostream &operator<<(ostream &out, const Evaluator &evaluator) {
    cout << "Accuracy Percentage is: " << evaluator.percentage_of_correctly_predicted_classes << "%%";

    cout << "Confusion Matrix: ";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << fixed;
            cout << setprecision(2);
            cout << evaluator.confusion_matrix[i][j] << "%%" << " ";
    }
    cout << '\n';
  }

  return out;
}




