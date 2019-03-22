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

using namespace std;


bool DataRetriever::RetrieveTrainingImages(string file) {
    ifstream my_input_file(file);

    if (my_input_file.is_open()) {
        while(!my_input_file.eof()) {
            ImagesReader image;
            my_input_file >> image;
            vector_of_images.push_back(image);
        }
        my_input_file.close();
        vector_of_images.pop_back();
        return true;
    } else {
        cout <<"Invalid file \n";
        return false;
    }
}

bool DataRetriever::RetrieveTrainingLabels(string file) {
    ifstream my_input_file(file);

    if (my_input_file.is_open()) {
        while(!my_input_file.eof()) {
            int number;
            my_input_file >> number;
            vector_of_labels.push_back(number);
        }
        my_input_file.close();
        return true;
    } else {
        cout <<"Invalid file \n";
        return false;
    }
}

//calculate

double DataRetriever::CalculateLikelihoodForEachIndex(int row, int col, int class_number, int feature) {
    int number_of_times_feature_occurs = 0;
    int number_of_times_class_occurs = 0;  

    int tracker = 0;
    while(tracker < vector_of_labels.size()) {
        if (vector_of_labels.at(tracker) == class_number) {
            number_of_times_class_occurs++;

            if (vector_of_images.at(tracker).actual_image[row][col] == feature) {
                number_of_times_feature_occurs++;
            }
        } 
        tracker++;
    }

    double likelihood_for_index = (smoothing_factor + number_of_times_feature_occurs) / (2*smoothing_factor + number_of_times_class_occurs);

    return likelihood_for_index;
}

double DataRetriever::CalculatePriorsProbability(int class_number) {
    int number_of_times_class_occurs = 0;  
    for(int i = 0; i < vector_of_labels.size(); i++) {
        if (vector_of_labels.at(i) == class_number) {
            number_of_times_class_occurs++;
        }
    }

    double probability_of_priors = (double) (number_of_times_class_occurs / vector_of_labels.size());
    return probability_of_priors;
}


//generate prob matrix
void DataRetriever::CreateProbabilityModel() {
    SetToZero(probability_model);

    SetLikelihoodToModel(probability_model);

    
}

void DataRetriever::SetToZero(double model[28][28][10][2]) {
for (int row = 0; row < kImageLength; row++) {
        for (int col = 0; col < kImageLength; col++) {
            for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
                for (int feature = 0; feature < 2; feature++) {
                        model[row][col][class_number][feature] = 0;
                    }
                }
            }
        }
}

void DataRetriever::SetLikelihoodToModel(double model[28][28][10][2]) {
    for (int row = 0; row < kImageLength; row++) {
        for (int col = 0; col < kImageLength; col++) {
            for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
                for (int feature = 0; feature < 2; feature++) {
                    model[row][col][class_number][feature] = CalculateLikelihoodForEachIndex(row, col, class_number, feature);
                }
            }
        }
    }
}



//save this model to a file



//load a model from a file