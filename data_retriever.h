#ifndef DATA_H
#define DATA_H

#include "image_reader.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class DataRetriever { 
    private:
        std::vector<ImagesReader> vector_of_images;
        std::vector<int> vector_of_labels;
    public:
        DataRetriever();
        bool RetrieveTrainingImages(string file);
        bool RetrieveTrainingLabels(string file);
        
};
#endif