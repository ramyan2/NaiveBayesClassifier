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
#include <utility>
#include <algorithm>

using namespace std;

DataRetriever::DataRetriever() {}

//need to create a model by training data
DataRetriever::DataRetriever(string training_images_file, string training_labels_file) {
    RetrieveTrainingImages(training_images_file);
    RetrieveTrainingLabels(training_labels_file);
}


//--------------//

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
        int number;
        while(my_input_file >> number) {
            vector_of_labels.push_back(number);
        }
        my_input_file.close();
        return true;
    } else {
        cout <<"Invalid file \n";
        return false;
    }
}

//------------//

//calculates likelihood for each index (helper for the model)
double DataRetriever::CalculateLikelihoodForEachIndex(int row, int col, int class_number, int feature) {
    int number_of_times_feature_occurs = 0;
    int number_of_times_class_occurs = 0;  

    unsigned long long tracker = 0;
    while(tracker < vector_of_labels.size()) {
        if (vector_of_labels.at(tracker) == class_number) {
            number_of_times_class_occurs++;

            ImagesReader image = vector_of_images.at(tracker);
            if (image.actual_image[row][col] == feature) {
                number_of_times_feature_occurs++;
            }
        } 
        tracker++;
    }

    double likelihood_for_index = (k_value + number_of_times_feature_occurs) / (2*k_value + number_of_times_class_occurs);
    
    return likelihood_for_index;
}


//----------------//


//calculates probability for a class
double DataRetriever::CalculatePriorsProbability(int class_number) {
    double number_of_times_class_occurs = 0.0;  
    for(int i = 0; i < vector_of_labels.size(); i++) {
        if (vector_of_labels.at(i) == (double) class_number) {
            number_of_times_class_occurs++;
        }
    }
  double probability_of_priors =
      (double) (number_of_times_class_occurs / vector_of_labels.size());
    return probability_of_priors;
}


//generates a vector for all priors
std::vector<double> DataRetriever::CreateVectorOfPriorsProbability() {
    std::vector<double> priors_vector;

    for (int i = 0; i < kNumberOfClasses; i++) {
        double probability = CalculatePriorsProbability(i);
        priors_vector.push_back(probability);
    }

    return priors_vector;
}

//-----------//


