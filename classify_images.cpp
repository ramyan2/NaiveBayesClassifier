#include "classify_images.h"
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

Classifier::Classifier() {}

//load a model from a file***

void Classifier::LoadModelFromFile(string probability_file) {
    ifstream my_input_file(probability_file);

    if (my_input_file.is_open()) {
        for (int row = 0; row < kImageLength; row++) {
            for (int col = 0; col < kImageLength; col++) {
                for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
                    for (int feature = 0; feature < 2; feature++) {
                        double specific_likelihood_value;
                        my_input_file >> specific_likelihood_value;

                        probability_model[row][col][class_number][feature] = specific_likelihood_value;
                    }
                }
            }
        }

        my_input_file.close();
    } else {
        cout << "Invalid file";
    }
}


