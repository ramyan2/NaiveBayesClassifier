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