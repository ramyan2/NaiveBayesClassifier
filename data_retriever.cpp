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

DataRetriever::DataRetriever() {}

//need to create a model by training data
DataRetriever::DataRetriever(string training_images_file, string training_labels_file) {
    RetrieveTrainingImages(training_images_file);
    RetrieveTrainingLabels(training_labels_file);

    // CreateProbabilityModel();
    // CreateVectorOfPriorsProbability();
}

//using stored trained model 

// DataRetriever::DataRetriever(string type, string stored_training_images_file, string stored_training_priors_file) {
//     LoadModelFromFile(stored_training_images_file);
//     LoadPriorsModelFromFile(stored_training_priors_file);
// }


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

// //helper to genereate prob matrix
// void DataRetriever::SetToZero(double model[28][28][10][2]) {
// for (int row = 0; row < kImageLength; row++) {
//         for (int col = 0; col < kImageLength; col++) {
//             for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
//                 for (int feature = 0; feature < 2; feature++) {
//                         model[row][col][class_number][feature] = 0;
//                     }
//                 }
//             }
//         }
// }
// //helper to generate prob matrix
// void DataRetriever::SetLikelihoodToModel(double model[28][28][10][2]) {
//     for (int row = 0; row < kImageLength; row++) {
//         for (int col = 0; col < kImageLength; col++) {
//             for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
//                 for (int feature = 0; feature < 2; feature++) {
//                     model[row][col][class_number][feature] = CalculateLikelihoodForEachIndex(row, col, class_number, feature);
//                 }
//             }
//         }
//     }
// }

// //generate prob matrix
// void DataRetriever::CreateProbabilityModel() {
//     SetToZero(probability_model);
//     SetLikelihoodToModel(probability_model);

//     cout << vector_of_images.at(999);

// }


//----------------//


//calculates probability for a class
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


// //save likelihood model to a file ***
// void DataRetriever::SaveModelToFile(string probability_file) {
//     cout <<"check";
//     ofstream my_output_file;
//     my_output_file.open(probability_file, std::ofstream::out | std::ofstream::trunc);

//     if (my_output_file.is_open()) {
        
//      for (int row = 0; row < kImageLength; row++) {
//             for (int col = 0; col < kImageLength; col++) {
//                 for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
//                     for (int feature = 0; feature < 2; feature++) {
//                         my_output_file << probability_model[row][col][class_number][feature];
//                     }
//                 }
//             }
//         }
//         my_output_file.close();
//         cout << "Probability Model is in " << probability_file;
//     } else {
//         cout << "Invalid output file";
//     }

// }

// //saves priors model to a file
// void DataRetriever::SavePriorsModelToFile(string priors_file) {
//     ofstream my_output_file;
//     my_output_file.open(priors_file, std::ofstream::out | std::ofstream::trunc);

//     if (my_output_file.is_open()) {
//      for (int i = 0; i < vector_of_labels.size(); i++) {
//         my_output_file << vector_of_labels.at(i) << endl;
//         }
//         my_output_file.close();
//         cout << "Priors Model is in " << priors_file;
//     } else {
//         cout << "Invalid output file";
//     }

// }

//----------//

// //load likelihood model from a file
// void DataRetriever::LoadModelFromFile(string probability_file) {
//     ifstream my_input_file(probability_file);

//     if (my_input_file.is_open()) {
//         for (int row = 0; row < kImageLength; row++) {
//             for (int col = 0; col < kImageLength; col++) {
//                 for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
//                     for (int feature = 0; feature < 2; feature++) {
//                         double specific_likelihood_value;
//                         my_input_file >> specific_likelihood_value;

//                         probability_model[row][col][class_number][feature] = specific_likelihood_value;
//                     }
//                 }
//             }
//         }

//         my_input_file.close();
//     } else {
//         cout << "Invalid file";
//     }
// }

// //load priors model from a file
// void DataRetriever::LoadPriorsModelFromFile(string priors_file) {
//     ifstream my_input_file(priors_file);

//     if (my_input_file.is_open()) {
//         double prior_probability;

//        while (my_input_file >> prior_probability) {
//             vector_of_labels.push_back(prior_probability);
//         }
//         my_input_file.close();
//     } else {
//         cout << "Invalid file";
//     }
// }

//-------------//

// int DataRetriever::CalculatePosteriorProbabilities(ImagesReader image) {
//     for (unsigned long long i = 0; i < kNumberOfClasses; i++) {
//         double posterior_probability = 0;

//         posterior_probability = posterior_probability + log(CalculatePriorsProbability(i));

//         for (int row = 0; row < kImageLength; row++) {
//             for (int col = 0; col < kImageLength; col++) {
//                 posterior_probability += log(probability_model[row][col][i][image.actual_image[row][col]]);
//             }
//         }

//         vector_of_posterior_probabilities.push_back(posterior_probability);
//     }

//         double max = vector_of_posterior_probabilities.at(0);
//         class_of_image = 0;
//         for (int i = 1; i < vector_of_posterior_probabilities.size(); i++) {
//             if (vector_of_posterior_probabilities.at(i) > max) {
//                 max = vector_of_posterior_probabilities.at(i);
//                 class_of_image = i;
//             }
//         }
//         return class_of_image;
//     }
