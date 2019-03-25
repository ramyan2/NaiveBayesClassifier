#include "evaluator.h"
#include "data_retriever.h"
#include "image_reader.h"
#include "classifier.h"
#include <math.h>  
#include <istream>
#include <sstream>
#include <ostream>
#include <iostream>
#include <fstream>



Classifier::Classifier() {}

Classifier::Classifier(string images_data_file, string labels_data_file) {
    DataRetriever model = DataRetriever(move(images_data_file), move(labels_data_file));
    
    CreateProbabilityModel(model);
    CreateProbabilityModel(model);
}


//helper to genereate prob matrix
void Classifier::SetToZero() {
for (int row = 0; row < kImageLength; row++) {
        for (int col = 0; col < kImageLength; col++) {
            for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
                for (int feature = 0; feature < 2; feature++) {
                        probability_model[row][col][class_number][feature] = 0;
                    }
                }
            }
        }
}
//helper to generate prob matrix
void Classifier::SetLikelihoodToModel(DataRetriever training_model) {
    for (int row = 0; row < kImageLength; row++) {
        for (int col = 0; col < kImageLength; col++) {
            for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
                for (int feature = 0; feature < 2; feature++) {
                    probability_model[row][col][class_number][feature] = training_model.CalculateLikelihoodForEachIndex(row, col, class_number, feature);
                }
            }
        }
    }
}

//generate prob matrix
void Classifier::CreateProbabilityModel(DataRetriever training_model) {
    SetToZero();
    SetLikelihoodToModel(training_model);
}


//Priors generator
void Classifier::CreatePriorsModel(DataRetriever training_model) {
    for (int i = 0; i < training_model.CreateVectorOfPriorsProbability.size(); i++) {
        priors_vector.push_back(training_model.CalculateLikelihoodForEachIndex.at(i));
    }
}


int Classifier::CalculatePosteriorProbabilities(ImagesReader image) {
    std::vector<double> vector_of_posteriors;
    for (unsigned long long i = 0; i < kNumberOfClasses; i++) {
        double posterior_probability = 0;

        posterior_probability = posterior_probability + log(priors_vector.at(i));

        for (int row = 0; row < kImageLength; row++) {
            for (int col = 0; col < kImageLength; col++) {
                posterior_probability += log(probability_model[row][col][i][image.actual_image[row][col]]);
            }
        }

        vector_of_posteriors.push_back(posterior_probability);
    }

        double max = vector_of_posteriors.at(0);

        int class_of_image = 0;
        for (int i = 1; i < vector_of_posteriors.size(); i++) {
            if (vector_of_posteriors.at(i) > max) {
                max = vector_of_posteriors.at(i);
                class_of_image = i;
            }
        }
        return class_of_image;
    }

//load likelihood model from a file
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

//load priors model from a file
void Classifier::LoadPriorsModelFromFile(string priors_file) {
    ifstream my_input_file(priors_file);

    if (my_input_file.is_open()) {
        double prior_probability;

       while (my_input_file >> prior_probability) {
            priors_vector.push_back(prior_probability);
        }
        my_input_file.close();
    } else {
        cout << "Invalid file";
    }
}

//save likelihood model to a file ***
void Classifier::SaveModelToFile(string probability_file) {
    ofstream my_output_file;
    my_output_file.open(probability_file, std::ofstream::out | std::ofstream::trunc);

    if (my_output_file.is_open()) {
        
     for (int row = 0; row < kImageLength; row++) {
            for (int col = 0; col < kImageLength; col++) {
                for (int class_number = 0; class_number < kNumberOfClasses; class_number++) {
                    for (int feature = 0; feature < 2; feature++) {
                        my_output_file << probability_model[row][col][class_number][feature];
                    }
                }
            }
        }
        my_output_file.close();
        cout << "Probability Model is in " << probability_file;
    } else {
        cout << "Invalid output file";
    }

}

//saves priors model to a file
void Classifier::SavePriorsModelToFile(string priors_file) {
    ofstream my_output_file;
    my_output_file.open(priors_file, std::ofstream::out | std::ofstream::trunc);

    if (my_output_file.is_open()) {
     for (int i = 0; i < priors_vector.size(); i++) {
        my_output_file << priors_vector.at(i) << endl;
        }
        my_output_file.close();
        cout << "Priors Model is in " << priors_file;
    } else {
        cout << "Invalid output file";
    }

}